# Vocal Leveler — AU development foundation

This is the initial JUCE/CMake source project for a macOS Audio Unit plugin.

## Compatibility target
- Universal macOS binary: `x86_64` (Intel) + `arm64` (Apple Silicon)
- Minimum deployment target: macOS 11 Big Sur
- Logic Pro Audio Unit format (`.component`)

## Important status
This is **not the finished vocal-leveling plugin**. It is the first buildable project foundation:
- AU plugin target and Universal architecture configuration
- starter UI and parameter controls
- Logic project parameter-state save/restore
- safe audio pass-through

The audio currently passes through unchanged. Automatic event/word detection, breath detection,
waveform capture, gain-map generation, 0.25 dB manual nudges, editing tools, and the absolute
peak ceiling still need to be implemented and tested. They are deliberately not represented
as working features in this prototype.

## Build on macOS
1. Install Xcode and its Command Line Tools.
2. Install CMake (for example with Homebrew).
3. Open Terminal in this folder.
4. Run:

   ```bash
   cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
   cmake --build build --config Release
   ```

CMake downloads JUCE 8.0.6 on the first configure, so an internet connection is required.
The resulting AU component should be in the build tree under the `VocalLeveler_artefacts`
directory. Check the exact path printed by CMake.

## Next implementation stages
1. Transfer/analyze state synchronized to Logic's host timeline.
2. Store a compact waveform overview and event/gain map in plugin state.
3. Automatic voice event and breath detection, with confidence-aware manual correction.
4. Phrase/event mode for non-vocal material.
5. Gain-map playback with smooth boundaries and a strict sample-peak ceiling.
6. Waveform editor, split/merge/correction, global breath processing and per-breath overrides.
7. Validation in Logic on both Intel and Apple Silicon Macs.

A Universal build setting does not by itself prove compatibility on every Mac. The AU must be
compiled, validated with `auval`, and tested in Logic on representative Intel and Apple Silicon
systems.
