import argparse
import math
import sys
import time

import numpy as np
import soundcard as sc
import sounddevice as sd


SAMPLE_RATE = 48000
BLOCK_SIZE = 1024
CHANNELS = 2
PRINT_FPS = 20

FREQ_BANDS = {
    "bass": (20, 250),
    "mid": (250, 4000),
    "high": (4000, 10000),
}


def list_devices() -> None:
    """Print loopback devices and PortAudio devices."""
    print("Soundcard loopback devices:")
    for index, mic in enumerate(sc.all_microphones(include_loopback=True)):
        if mic.isloopback:
            print(f"  [{index}] {mic.name} ({mic.channels} channels)")

    print("\nSounddevice / PortAudio devices:")
    print(sd.query_devices())


def _hostapi_name(index: int) -> str:
    return sd.query_hostapis(index)["name"]


def find_default_wasapi_output_device() -> int:
    """Return the default Windows WASAPI output device index."""
    hostapis = sd.query_hostapis()
    wasapi_index = None

    for index, hostapi in enumerate(hostapis):
        if "WASAPI" in hostapi["name"].upper():
            wasapi_index = index
            break

    if wasapi_index is None:
        raise RuntimeError("No WASAPI host API found. System loopback capture is Windows-only.")

    default_output = hostapis[wasapi_index]["default_output_device"]
    if default_output < 0:
        raise RuntimeError("No default WASAPI output device found.")

    return default_output


def resolve_capture_settings(device_id: int | None) -> tuple[int, int, int]:
    """Resolve device, sample rate and channel count for loopback capture."""
    device_id = find_default_wasapi_output_device() if device_id is None else device_id
    info = sd.query_devices(device_id)

    if "WASAPI" not in _hostapi_name(info["hostapi"]).upper():
        raise RuntimeError(
            f"Device {device_id} is not a WASAPI device. Use --list-devices to choose a WASAPI output device."
        )

    channels = min(CHANNELS, int(info["max_output_channels"]))
    if channels <= 0:
        raise RuntimeError(f"Device {device_id} is not an output device.")

    sample_rate = int(info["default_samplerate"] or SAMPLE_RATE)
    return device_id, sample_rate, channels


def band_indexes(sample_rate: int, block_size: int) -> dict[str, tuple[int, int]]:
    indexes = {}
    for name, (low, high) in FREQ_BANDS.items():
        low_index = max(1, int(low * block_size / sample_rate))
        high_index = min(block_size // 2, int(high * block_size / sample_rate))
        indexes[name] = (low_index, max(low_index + 1, high_index))
    return indexes


def make_bar(value: float, width: int = 32) -> str:
    filled = max(0, min(width, int(value * width)))
    return "#" * filled + "-" * (width - filled)


def analyze_audio(block: np.ndarray, sample_rate: int, indexes: dict[str, tuple[int, int]]) -> dict[str, float]:
    mono = block.mean(axis=1) if block.ndim == 2 else block
    mono = mono.astype(np.float32, copy=False)

    rms = float(np.sqrt(np.mean(np.square(mono)))) if mono.size else 0.0
    peak = float(np.max(np.abs(mono))) if mono.size else 0.0

    windowed = mono * np.hanning(len(mono))
    fft_data = np.abs(np.fft.rfft(windowed))

    bands = {}
    for name, (low, high) in indexes.items():
        bands[name] = float(np.mean(fft_data[low:high])) if high > low else 0.0

    # These factors are display gains, not audio gains.
    return {
        "rms": min(rms * 4.0, 1.0),
        "peak": min(peak, 1.0),
        "bass": min(bands["bass"] * 0.04, 1.0),
        "mid": min(bands["mid"] * 0.08, 1.0),
        "high": min(bands["high"] * 0.18, 1.0),
        "dbfs": 20.0 * math.log10(max(rms, 1e-9)),
    }


def normalize_name(name: str) -> str:
    return " ".join(name.lower().replace("loopback:", "").split())


def find_loopback_microphone(device_id: int | None, loopback_index: int | None):
    loopbacks = [mic for mic in sc.all_microphones(include_loopback=True) if mic.isloopback]
    if not loopbacks:
        raise RuntimeError("No loopback audio devices found.")

    if loopback_index is not None:
        if loopback_index < 0 or loopback_index >= len(loopbacks):
            raise RuntimeError(f"Loopback index {loopback_index} is out of range.")
        return loopbacks[loopback_index]

    if device_id is None:
        speaker_name = sc.default_speaker().name
    else:
        speaker_name = sd.query_devices(device_id)["name"]

    target = normalize_name(speaker_name)
    for mic in loopbacks:
        mic_name = normalize_name(mic.name)
        if target in mic_name or mic_name in target:
            return mic

    available = ", ".join(mic.name for mic in loopbacks)
    raise RuntimeError(f"No loopback device matches '{speaker_name}'. Available loopbacks: {available}")


def run_listener(device_id: int | None, loopback_index: int | None) -> None:
    microphone = find_loopback_microphone(device_id, loopback_index)
    sample_rate = SAMPLE_RATE
    channels = min(CHANNELS, int(microphone.channels))
    indexes = band_indexes(sample_rate, BLOCK_SIZE)

    print("System audio listener started.")
    print(f"Device: {microphone.name}")
    print(f"Sample rate: {sample_rate}, channels: {channels}, block: {BLOCK_SIZE}")
    print("Play music in Kugou or a browser. Press Ctrl+C to stop.\n")

    last_print = 0.0
    smooth = {"rms": 0.0, "peak": 0.0, "bass": 0.0, "mid": 0.0, "high": 0.0, "dbfs": -180.0}
    with microphone.recorder(samplerate=sample_rate, channels=channels, blocksize=BLOCK_SIZE) as recorder:
        while True:
            block = recorder.record(numframes=BLOCK_SIZE)
            values = analyze_audio(block, sample_rate, indexes)

            for key, value in values.items():
                if key == "dbfs":
                    smooth[key] = value
                else:
                    smooth[key] = smooth[key] * 0.75 + value * 0.25

            now = time.perf_counter()
            if now - last_print < 1.0 / PRINT_FPS:
                continue
            last_print = now

            line = (
                f"\rRMS [{make_bar(smooth['rms'])}] {smooth['rms']:.3f} "
                f"Peak {smooth['peak']:.3f} "
                f"dBFS {smooth['dbfs']:6.1f} | "
                f"B {smooth['bass']:.3f} M {smooth['mid']:.3f} H {smooth['high']:.3f}"
            )
            print(line, end="", flush=True)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Listen to Windows system output audio, including Kugou and browser playback."
    )
    parser.add_argument("--list-devices", action="store_true", help="print audio devices and exit")
    parser.add_argument("--device", type=int, default=None, help="PortAudio output device id, such as 12 or 13")
    parser.add_argument("--loopback-index", type=int, default=None, help="loopback index from --list-devices")
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    if args.list_devices:
        list_devices()
        return 0
    try:
        run_listener(args.device, args.loopback_index)
    except KeyboardInterrupt:
        print("\nStopped.")
        return 0
    except Exception as exc:
        print(f"Error: {exc}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    raise SystemExit(main())
