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

PALETTES = {
    "rainbow": (),
    "neon": (
        (120, 40, 255),   # violet
        (0, 170, 255),    # electric blue
        (0, 255, 190),    # mint cyan
        (255, 230, 40),   # lemon
        (255, 70, 120),   # hot pink
    ),
    "aurora": (
        (45, 85, 255),
        (0, 230, 210),
        (80, 255, 135),
        (210, 255, 90),
        (255, 120, 70),
    ),
    "cyber": (
        (40, 30, 255),
        (0, 255, 255),
        (80, 255, 60),
        (255, 255, 0),
        (255, 25, 80),
    ),
    "sunset": (
        (70, 30, 170),
        (210, 55, 190),
        (255, 80, 90),
        (255, 145, 40),
        (255, 220, 70),
    ),
    "candy": (
        (255, 70, 190),
        (140, 90, 255),
        (40, 210, 255),
        (80, 255, 170),
        (255, 245, 90),
    ),
}

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


def blend_rgb(a: tuple[int, int, int], b: tuple[int, int, int], t: float) -> tuple[int, int, int]:
    t = clamp(t)
    return (
        int(a[0] + (b[0] - a[0]) * t),
        int(a[1] + (b[1] - a[1]) * t),
        int(a[2] + (b[2] - a[2]) * t),
    )


def sample_palette(palette: tuple[tuple[int, int, int], ...], position: float) -> tuple[int, int, int]:
    position = clamp(position)
    scaled = position * (len(palette) - 1)
    index = int(scaled)
    if index >= len(palette) - 1:
        return palette[-1]
    return blend_rgb(palette[index], palette[index + 1], scaled - index)


def rainbow_bar_color(
    col: int,
    row_from_bottom: int,
    level: float,
    frame_index: int,
    brightness: float,
) -> tuple[int, int, int]:
    """Colorful rolling rainbow, similar to the firmware rainbow mode."""
    column_phase = col / max(1, COLUMNS - 1)
    row_phase = row_from_bottom / max(1, ROWS - 1)
    hue = (frame_index * 0.018 + column_phase * 0.78 + row_phase * 0.16) % 1.0
    saturation = clamp(0.92 + level * 0.08)
    value = clamp(brightness * (0.48 + row_phase * 0.22 + level * 0.42))
    return hsv_rgb(hue, saturation, value)


def palette_bar_color(
    col: int,
    row_from_bottom: int,
    level: float,
    frame_index: int,
    brightness: float,
    palette: tuple[tuple[int, int, int], ...],
) -> tuple[int, int, int]:
    """Smooth music-bar palette without white peak dots."""
    column_t = col / max(1, COLUMNS - 1)
    # Add a very slow color drift so the effect stays alive even on steady music.
    drift = 0.08 * math.sin(frame_index * 0.025 + col * 0.35)
    base = sample_palette(palette, (column_t + drift) % 1.0)

    # Higher rows are hotter/brighter, like a polished visualizer.
    row_t = row_from_bottom / max(1, ROWS - 1)
    hot = sample_palette(palette, clamp(0.72 + row_t * 0.22))
    warm = blend_rgb(base, hot, row_t * 0.36)
    shimmer = 0.92 + 0.08 * math.sin(frame_index * 0.18 + col * 0.65 + row_from_bottom * 0.4)
    scale = clamp(brightness * (0.50 + row_t * 0.32 + level * 0.30) * shimmer)
    return int(warm[0] * scale), int(warm[1] * scale), int(warm[2] * scale)


def build_vertical_frame(
    columns: np.ndarray,
    brightness: float,
    frame_index: int,
    palette: tuple[tuple[int, int, int], ...] = PALETTES["rainbow"],
) -> bytes:
    """Convert 14 smooth column levels into a flowing vertical bar frame."""
    frame = [(0, 0, 0)] * LED_COUNT

    for col, level in enumerate(columns):
        level = clamp(float(level))
        height = level * (ROWS + 0.25)

        for row in range(ROWS):
            led_index = KEY_TO_LED_MAP[row][col]
            if led_index == INVALID_LED:
                continue

            row_from_bottom = ROWS - 1 - row
            fill = clamp(height - row_from_bottom)
            if fill <= 0.0:
                continue

            # Partial fill gives the 5-row keyboard smoother motion instead of stepping.
            edge_softness = 0.20 + 0.80 * fill
            if palette:
                r, g, b = palette_bar_color(col, row_from_bottom, level, frame_index, brightness, palette)
            else:
                r, g, b = rainbow_bar_color(col, row_from_bottom, level, frame_index, brightness)
            frame[led_index] = (
                int(r * edge_softness),
                int(g * edge_softness),
                int(b * edge_softness),
            )

    payload = bytearray()
    for r, g, b in frame:
        payload.extend((r, g, b))
    return bytes(payload)


class VerticalMusicLighting:
    def __init__(self, vid: int, pid: int, fps: int, gain: float, brightness: float, palette_name: str):
        self.conn = HidConnection(vid=vid, pid=pid)
        self.conn.on_status_changed = self.on_status_changed
        self.connected = False
        self.frame_interval = 1.0 / fps
        self.gain = gain
        self.brightness = clamp(brightness)
        self.palette_name = palette_name
        self.palette = PALETTES[palette_name]
        self.columns = np.zeros(COLUMNS, dtype=np.float32)
        self.energy_floor = np.ones(COLUMNS, dtype=np.float32) * 0.02
        self.energy_ceiling = np.ones(COLUMNS, dtype=np.float32) * 0.70
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
        rms = float(np.sqrt(np.mean(np.square(block)))) if block.size else 0.0

        # Normalize against a slowly adapting range, so bars keep moving across songs.
        span = np.maximum(self.energy_ceiling - self.energy_floor, 0.12)
        normalized = np.clip((raw_columns - self.energy_floor) / span, 0.0, 1.0)
        normalized = np.power(normalized, 1.08)
        normalized[normalized < 0.035] = 0.0

        # Neighbor blending makes adjacent columns flow like a real visualizer.
        blended = normalized.copy()
        for index in range(COLUMNS):
            left = normalized[index - 1] if index > 0 else normalized[index]
            right = normalized[index + 1] if index + 1 < COLUMNS else normalized[index]
            blended[index] = normalized[index] * 0.70 + max(left, right) * 0.18 + min(left, right) * 0.12
        normalized = np.clip(blended, 0.0, 1.0)

        self.energy_floor = np.minimum(self.energy_floor * 0.997 + raw_columns * 0.003, raw_columns * 0.80)
        target_ceiling = np.maximum(raw_columns, 0.40)
        rising_ceiling = target_ceiling > self.energy_ceiling
        self.energy_ceiling[rising_ceiling] = (
            self.energy_ceiling[rising_ceiling] * 0.80 + target_ceiling[rising_ceiling] * 0.20
        )
        self.energy_ceiling[~rising_ceiling] = (
            self.energy_ceiling[~rising_ceiling] * 0.990 + target_ceiling[~rising_ceiling] * 0.010
        )

        # Fast attack, smooth release. No stepped peak caps, so the motion is fluid.
        rising = normalized > self.columns
        self.columns[rising] = self.columns[rising] * 0.18 + normalized[rising] * 0.82
        self.columns[~rising] = self.columns[~rising] * 0.86 + normalized[~rising] * 0.14

        now = time.perf_counter()
        if now - self.last_send < self.frame_interval:
            return False, rms

        rgb_frame = build_vertical_frame(self.columns, self.brightness, self.frame_index, self.palette)
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
        print(
            f"Vertical lighting: {COLUMNS} columns x {ROWS} rows, "
            f"fps={1.0 / self.frame_interval:.0f}, palette={self.palette_name}"
        )
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
    parser.add_argument("--fps", type=int, default=38, help="lighting frame rate")
    parser.add_argument("--gain", type=float, default=10.0, help="spectrum display gain")
    parser.add_argument("--brightness", type=float, default=0.88, help="0.0 to 1.0 output brightness")
    parser.add_argument(
        "--palette",
        choices=tuple(PALETTES.keys()),
        default="rainbow",
        help="color palette",
    )
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
        palette_name=args.palette,
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
