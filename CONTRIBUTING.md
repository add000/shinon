# Contributing to Shinon

Thanks for helping! No CLA or DCO is required. By contributing you agree your work is licensed GPL-3.0-or-later.

- `core/` is plain C++17 with no Android dependency. Keep it that way so it can be tested on a PC.
- Audio-thread code: **no allocation, locks, file I/O, or JNI.**
- Add a unit test for every DSP change. Compare against a reference (REW/Python) where possible.
- Do not copy code from projects whose license is incompatible with GPL-3.0-or-later.
- Compatibility reports (device, Android version, app tested) are very welcome: see docs/COMPATIBILITY.md.
- Add the SPDX header to new source files.
