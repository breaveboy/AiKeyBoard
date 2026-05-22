import argparse
import colorsys
import math
import sys
import time

import numpy as np

from connection import DevStatus, HidConnection
from constants import Cmd
from listen_system_audio import (
    BLOCK_SIZE,
    CHANNELS,
    SAMPLE_RATE,
    find_loopback_microphone,
    list_devices,
    make_bar,
)
from protocol import Protocol


LED_COUNT = 61
ROWS = 5
COLUMNS = 14
INVALID_LED = 0xFF
PACKET_SIZES = (54, 54, 54, 21)

# Same physical matrix-to-LED map as Lib/src/lib_ws2812.c.
KEY_TO_LED_MAP = (
    (0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13),
    (27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14),
    (28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, INVALID_LED, 40),
    (52, INVALID_LED, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, INVALID_LED, 41),
    (53, 54, 55, INVALID_LED, INVALID_LED, INVALID_LED, 56, INVALID_LED, INVALID_LED, INVALID_LED, 57, 58, 59, 60),
)


def clamp(value: float, low: float = 0.0, high: float = 1.0) -> float:
    return max(low, min(high, value))


def hsv_rgb(hue: float, saturation: float, value: float) -> tuple[int, int, int]:
    r, g, b = colorsys.hsv_to_rgb(hue % 1.0, clamp(saturation), clamp(value))
    return int(r * 255), int(g * 255), int(b * 255)


def build_log_frequency_bins(sample_rate: int, block_size: int, columns: int) -> list[tuple[int, int]]:
    """Build 14 logarithmic frequency bins, from bass on the left to treble on the right."""
    low_hz = 35.0
    high_hz = min(12000.0, sample_rate / 2.0)
    edges = np.geomspace(low_hz, high_hz, columns + 1)
    bins = []
    for start_hz, end_hz in zip(edges[:-1], edges[1:]):
        start = max(1, int(start_hz * block_size / sample_rate))
        end = min(block_size // 2, int(end_hz * block_size / sample_rate))
        bins.append((start, max(start + 1, end)))
    return bins


def spectrum_columns(block: np.ndarray, bins: list[tuple[int, int]], gain: float) -> np.ndarray:
    mono = block.mean(axis=1) if block.ndim == 2 else block
    mono = mono.astype(np.float32, copy=False)
    if mono.size == 0:
        return np.zeros(len(bins), dtype=np.float32)

    windowed = mono * np.hanning(len(mono))
    spectrum = np.abs(np.fft.rfft(windowed))
    values = []

    for start, end in bins:
        energy = float(np.mean(spectrum[start:end])) if end > start else 0.0
        # Log compression keeps quiet music visible without letting bass flatten everything.
        value = math.log1p(energy * gain) / math.log1p(gain * 10.0)
        values.append(clamp(value))

    return np.asarray(values, dtype=np.float32)


def build_vertical_frame(columns: np.ndarray, brightness: float, frame_index: int) -> bytes:
    """Convert 14 column levels into a 61 LED RGB frame ordered by LED index."""
    frame = [(0, 0, 0)] * LED_COUNT
    beat = float(np.mean(columns))

    for col, level in enumerate(columns):
        height = level * ROWS
        # Low columns are blue/cyan, mids green/yellow, highs pink/purple.
        hue = 0.58 - 0.75 * (col / max(1, COLUMNS - 1))
        hue += 0.018 * math.sin((frame_index * 0.12) + col * 0.7)

        for row in range(ROWS):
            led_index = KEY_TO_LED_MAP[row][col]
            if led_index == INVALID_LED:
                continue

            distance_from_bottom = ROWS - 1 - row
            segment = clamp(height - distance_from_bottom)
            if segment <= 0.0:
                continue

            row_boost = 0.50 + (distance_from_bottom / max(1, ROWS - 1)) * 0.50
            value = clamp((0.12 + segment * 0.88) * row_boost * brightness)
            saturation = clamp(0.85 + beat * 0.15)
            frame[led_index] = hsv_rgb(hue, saturation, value)

    payload = bytearray()
    for r, g, b in frame:
        payload.extend((r, g, b))
    return bytes(payload)


class VerticalMusicLighting:
    def __init__(self, vid: int, pid: int, fps: int, gain: float, brightness: float):
        self.conn = HidConnection(vid=vid, pid=pid)
        self.conn.on_status_changed = self.on_status_changed
        self.connected = False
        self.frame_interval = 1.0 / fps
        self.gain = gain
        self.brightness = clamp(brightness)
        self.columns = np.zeros(COLUMNS, dtype=np.float32)
        self.frame_index = 0
        self.last_send = 0.0

    def on_status_changed(self, status: DevStatus) -> None:
        self.connected = status == DevStatus.CONNECTED
        print(f"\nKeyboard status: {status.name}")

    def wait_for_keyboard(self) -> None:
        self.conn.start()
        print("Waiting for keyboard HID interface...")
        while not self.connected:
            time.sleep(0.1)

    def stop(self) -> None:
        self.conn.stop()

    def send_frame(self, rgb_frame: bytes) -> bool:
        if len(rgb_frame) != LED_COUNT * 3:
            raise ValueError(f"RGB frame must be {LED_COUNT * 3} bytes.")
        if not self.connected:
            return False

        offset = 0
        for cur_pkt, size in enumerate(PACKET_SIZES):
            payload = rgb_frame[offset : offset + size]
            offset += size
            packet = Protocol.encode(
                cmd=Cmd.LIGHT_MUSIC,
                param=0x00,
                res=0,
                total=len(PACKET_SIZES),
                cur=cur_pkt,
                payload=payload,
            )
            if not self.conn.send(packet):
                return False
            time.sleep(0.0012)
        return True

    def process_audio_block(self, block: np.ndarray, bins: list[tuple[int, int]]) -> tuple[bool, float]:
        raw_columns = spectrum_columns(block, bins, self.gain)
        # Fast attack, slower release: columns jump with beats and fall smoothly.
        rising = raw_columns > self.columns
        self.columns[rising] = self.columns[rising] * 0.30 + raw_columns[rising] * 0.70
        self.columns[~rising] = self.columns[~rising] * 0.84 + raw_columns[~rising] * 0.16

        rms = float(np.sqrt(np.mean(np.square(block)))) if block.size else 0.0
        now = time.perf_counter()
        if now - self.last_send < self.frame_interval:
            return False, rms

        rgb_frame = build_vertical_frame(self.columns, self.brightness, self.frame_index)
        sent = self.send_frame(rgb_frame)
        self.last_send = now
        self.frame_index += 1
        return sent, rms

    def run(self, loopback_index: int | None, device_id: int | None) -> None:
        microphone = find_loopback_microphone(device_id, loopback_index)
        channels = min(CHANNELS, int(microphone.channels))
        bins = build_log_frequency_bins(SAMPLE_RATE, BLOCK_SIZE, COLUMNS)

        self.wait_for_keyboard()
        print(f"Audio source: {microphone.name}")
        print(f"Vertical lighting: {COLUMNS} columns x {ROWS} rows, fps={1.0 / self.frame_interval:.0f}")
        print("Play Kugou or browser audio. Press Ctrl+C to stop.\n")

        last_print = 0.0
        with microphone.recorder(samplerate=SAMPLE_RATE, channels=channels, blocksize=BLOCK_SIZE) as recorder:
            while True:
                block = recorder.record(numframes=BLOCK_SIZE)
                sent, rms = self.process_audio_block(block, bins)

                now = time.perf_counter()
                if now - last_print >= 0.05:
                    last_print = now
                    avg = float(np.mean(self.columns))
                    peak = float(np.max(self.columns))
                    status = "TX" if sent else "--"
                    print(
                        f"\r{status} RMS [{make_bar(min(rms * 4.0, 1.0), 24)}] "
                        f"avg={avg:.3f} peak={peak:.3f}",
                        end="",
                        flush=True,
                    )


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Stream PC system audio as vertical music-reactive lighting to the keyboard."
    )
    parser.add_argument("--list-devices", action="store_true", help="print audio devices and exit")
    parser.add_argument("--loopback-index", type=int, default=None, help="loopback index from --list-devices")
    parser.add_argument("--device", type=int, default=None, help="PortAudio output device id, such as 12 or 13")
    parser.add_argument("--vid", type=lambda value: int(value, 0), default=0x36B7, help="keyboard VID")
    parser.add_argument("--pid", type=lambda value: int(value, 0), default=0xFFFF, help="keyboard PID")
    parser.add_argument("--fps", type=int, default=30, help="lighting frame rate")
    parser.add_argument("--gain", type=float, default=8.0, help="spectrum display gain")
    parser.add_argument("--brightness", type=float, default=0.75, help="0.0 to 1.0 output brightness")
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    if args.list_devices:
        list_devices()
        return 0

    app = VerticalMusicLighting(
        vid=args.vid,
        pid=args.pid,
        fps=max(1, min(args.fps, 60)),
        gain=max(0.1, args.gain),
        brightness=args.brightness,
    )

    try:
        app.run(loopback_index=args.loopback_index, device_id=args.device)
    except KeyboardInterrupt:
        print("\nStopped.")
        return 0
    except Exception as exc:
        print(f"\nError: {exc}", file=sys.stderr)
        return 1
    finally:
        app.stop()


if __name__ == "__main__":
    raise SystemExit(main())
