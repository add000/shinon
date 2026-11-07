# Shinon (深音)

**Node-based headphone tuning for Android** — system-wide audio processing, no player.

> Status: **pre-alpha / experimental.** Requires [Shizuku](https://shizuku.rikka.app/). May not work on every device or Android version.

Shinon captures audio from other apps, processes it through a graph of nodes, and plays it back to your headphones.

## Features (planned)

- **Headphone calibration** — headphone model + target frequency response → correction
- **IIR filter bank** — parametric EQ and a draggable FR editor with auto-fit to biquads
- **Spatial audio** — import your own `.sofa` (HRTF) files
- **Node graph core** — small, stable core; every feature is a node

## How it works

```
other apps → AudioPlaybackCapture → shinon-core (graph of nodes) → Oboe → headphones
                  Shizuku = setup/permissions only, audio never goes through it
```

## Known limitations

- Needs Shizuku running (must be restarted after reboot on non-rooted devices)
- Apps that block audio capture will not be processed
- Bluetooth headphones add latency, and built-in DSP in some headphones can invalidate calibration

## SOFA files

Shinon does **not** ship any `.sofa` files. Import your own (e.g. a personal measurement or a public dataset) from within the app. Check the license of any dataset you download.

## Privacy

Audio is processed on-device only. Shinon does not send audio or usage data anywhere. See [SECURITY.md](SECURITY.md).

## Build

```
cmake -S core -B build && cmake --build build && ctest --test-dir build
```

## License

GPL-3.0-or-later. See [LICENSE](LICENSE). Data files under `data/` carry their own licenses (see [docs/DATA_SOURCES.md](docs/DATA_SOURCES.md)).

Copyright (c) 2026 add000
# shinon
