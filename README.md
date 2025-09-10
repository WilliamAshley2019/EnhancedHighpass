# EnhancedHighpass

**EnhancedHighpass** is a VST3 highpass filter plugin built with JUCE 8, designed for trance EDM production. It features a clean, high-quality
Butterworth highpass filter with intuitive controls for cutoff frequency, resonance, gain, and dry/wet mix.
Inspired by Airwindows' **Highpass** plugin, it incorporates a high-quality dithering algorithm and a user-friendly 
UI with labeled knobs, making it ideal for removing low-end rumble from trance pads, leads, or basslines while maintaining 
clarity and polish.

## Features
- **Highpass Filter**: Second-order Butterworth highpass filter with a cutoff range of 20 Hz to 20 kHz (default: 200 Hz).
- **Resonance (Q)**: Adjustable from 0.1 to 10 (default: 0.707) for subtle to aggressive filter emphasis, inspired by Airwindows' "Loose/Tight" parameter.
- **Gain Control**: -24 dB to +24 dB (default: 0 dB) to adjust output level, inspired by Airwindows' **XLowpass**.
- **Dry/Wet Mix**: 0–100% (default: 100%) for blending filtered and unfiltered signals, perfect for parallel processing in trance mixes.
- **Dithering**: Airwindows-style dithering to reduce quantization noise, ensuring clean high-frequency output.
- **UI**: Modern interface with labeled knobs ("Cutoff", "Resonance", "Gain", "Dry/Wet") for intuitive control, styled like **LushAlpha**.
- **Optimized for Trance**: Default settings tailored for trance EDM, providing clear, sparkling highs and precise low-end control.

## Installation
1. **Prerequisites**:
   - DAW supporting VST3 plugins (e.g., FL Studio (tested), Ableton Live).
   - Windows (Visual Studio 2022 recommended for building).
   - JUCE 8 framework installed (`C:\Development\JUCE`).

2. **Building**: The four JUCE files are included in the main directory. Start a plugin basics project with the addition
3. of the dsp module to build.

## Usage
- **Cutoff**: Adjusts the highpass cutoff frequency (20 Hz–20 kHz). Set around 200 Hz to remove sub-bass rumble.
- **Resonance**: Controls filter emphasis near the cutoff. Use low values for smooth filtering or higher for pronounced effects.
- **Gain**: Boosts or attenuates the output (-24 dB to +24 dB) to balance levels in your mix.
- **Dry/Wet**: Blends the filtered signal with the original. Use partial wet settings (e.g., 50%) for parallel processing.
- Test in your DAW to ensure clean high-frequency output and effective low-end removal.

## License
**EnhancedHighpass** is licensed under the **GNU General Public License v3.0 (GPLv3)**. See `LICENSE` for full details.

### Airwindows Code
The dithering algorithm in `PluginProcessor.cpp` is derived from Airwindows' 
**Highpass** plugin, which is licensed under the **MIT License**. 
The original copyright holder for this code is Chris Johnson (Airwindows). See the Airwindows license notice
https://github.com/airwindows/airwindows
MIT License

Copyright (c) 2018 Chris Johnson

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.


