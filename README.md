# wir3d // PROTOCOL 07

<div align="center">

```
  ██     ██ ██ ██████  ██████  ██████  
  ██     ██ ██ ██   ██      ██ ██   ██ 
  ██  █  ██ ██ ██████   █████  ██   ██ 
  ██ ███ ██ ██ ██   ██      ██ ██   ██ 
   ███ ███  ██ ██   ██ ██████  ██████  
```

**Cyberpunk Vocal Pitch Shifter, Scale Autotune, Dimension Harmonizer Ping-Pong Delay & Glitch Unit**  
*Inspired by Serial Experiments Lain & The Matrix Aesthetic*

[![Format](https://img.shields.io/badge/Format-VST3%20%7C%20Standalone-00ff66?style=flat-square)](https://github.com/)
[![Framework](https://img.shields.io/badge/Framework-JUCE%208-00ff66?style=flat-square)](https://juce.com/)
[![C++](https://img.shields.io/badge/C%2B%2B-17-00ff66?style=flat-square)](https://en.cppreference.com/)
[![License](https://img.shields.io/badge/License-MIT-00ff66?style=flat-square)](LICENSE)

</div>

---

## ⚡ Overview

**wir3d** is an anime cyberpunk vocal effect processor developed with **JUCE 8** and modern C++17. Designed for live and studio production, it blends surgical real-time scale pitch correction with creative spatial and rhythmic glitch effects, zero-lookup atomic DSP performance, and an analog-modeled soft-knee ceiling limiter.

---

## 🔮 Key Features

* **Zero-Lookup Real-Time Thread Performance**: All parameters are cached into atomic pointers upon initialization, removing all string hashes and map lookups from `processBlock` for pure 0-cycle overhead.
* **Input Gain & Output Trim Staging**: Complete headroom calibration (-12 dB to +12 dB) to feed the pitch detector its optimal vocal signal and control final master output.
* **Analog Soft-Knee Output Ceiling**: Transparent under -3 dB with smooth tube/analog saturation curve approaching 0 dBFS to prevent harsh digital clipping when vocal layers and echoes sum together.
* **High-Precision YIN Pitch Detection**: Sliding-window tracking running every 128 samples (~2.9 ms) with sub-sample parabolic interpolation and subharmonic de-octaving (divisors 2, 3, and 4) to eliminate octave jumping.
* **Target Locking & Hysteresis**: Prevents vibrato flutter by locking to scale notes with intelligent hysteresis thresholds.
* **Speed Response**:
  * **92% – 100%**: Instantaneous hard robotic quantize (0 ms snap, T-Pain / Cher style).
  * **0% – 91%**: Exponential glide (2 ms to 350 ms) for natural, transparent portamento.
* **Dimension Stereo Harmonizer**: +7 semitones fifth with dual micro-detune (L -8 cents, R +8 cents) and 0.42 Hz quadrature LFO modulation before feeding the tape-filtered Ping-Pong delay.
* **BEAT REPEAT & Glitch Filter**: Real-time slice capture and looping (`1/4`, `1/8`, `1/16`, `1/32`, and `Glitch` 25 ms) with dedicated Dry/Wet control and resonant cyber bandpass filter.
* **SMILE Macro with Analog Tape Drift**: Rising high-pass sweep, atmospheric echo bloom with subtle tape wow & flutter, and tube saturation.
* **Master Filter**: Bipolar master tone shaper (Left: warm Low-Pass 20 kHz $\to$ 180 Hz; Right: crisp High-Pass 20 Hz $\to$ 3.8 kHz) with perceptual frequency skew.
* **Multi-Scale Quantizer**: Chromatic, Major, Minor, Major Pentatonic, Minor Pentatonic, Blues, Dorian, Phrygian, and Mixolydian.
* **Vocal Range Selector**: Wide (All), Low (Bass/Bari), Mid (Tenor/Alto), and High (Soprano).
* **Preset System**: Factory presets + user preset saving directly from the UI.
* **Matrix / Lain UI**: Custom CRT scanline aesthetic, phosphor laser green meters, and vector Lain Iwakura cyberpunk mascot.

---

## 🎛 Controls

| Control | Range | Description |
|---|---|---|
| **INPUT** | -12 to +12 dB | Input gain staging into YIN pitch detector. |
| **BEND** | -12 to +12 st | Continuous manual pitch transposition. |
| **TUNE** | 0 to 100% | Scale correction depth. |
| **SPEED** | 0 to 100% | Transition speed: smooth glides (0%) to hard snap (100%). |
| **HARMO** | 0 to 100% | Dimension stereo harmonizer (+7 st) and ping-pong delay wet mix. |
| **SMILE** | 0 to 100% | High-pass bloom, space echo and tube saturation macro. |
| **OUTPUT** | -12 to +12 dB | Master output trim before analog soft ceiling limiter. |
| **RPT MIX** | 0 to 100% | Beat repeat loop dry/wet blend. |
| **DIVISION** | Choice | Beat repeat slice division (`1/4`, `1/8`, `1/16`, `1/32`, `Glitch`). |
| **FILTER** | -100 to +100 | Master bipolar filter: LP (`< 0`) $\leftrightarrow$ HP (`> 0`). Center is bypass. |
| **KEY / SCALE** | Choice | Target musical root key and scale. |
| **RANGE** | Choice | Optimizes YIN tracking for specific vocal ranges. |
| **PRESET / SAVE**| Choice / Btn | Instant patch recall and user preset persistence. |

---

## 🛠 Building from Source

### Requirements
* [CMake 3.22+](https://cmake.org/download/)
* [Git](https://git-scm.com/)
* C++17 compatible compiler (Visual Studio 2022 on Windows, Xcode on macOS, GCC/Clang on Linux)

### Quick Build (Windows PowerShell)

```powershell
cd "wir3d"
cmake -B build -S .
cmake --build build --config Release
```

The compiled VST3 binary will be generated at:
```
build/WIR3D_artefacts/Release/VST3/wir3d.vst3
```

---

## 📜 License

Distributed under the **MIT License**. See `LICENSE` for details.
