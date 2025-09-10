This plugin is provided GPLv3 with exclusion of any sourcecode that was drawn from Airwindows Highpass.cpp or Highpass.h see below for more details.

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
 **Prerequisites**:
   - DAW supporting VST3 plugins (e.g., FL Studio (tested), or likely any other VST3 suppurting daw - it was tested on windows 11).
   - Windows (Visual Studio 2022 recommended for building).
   - JUCE 8 framework installed - Juce 8.09 was used.

 **Building**: The four JUCE files are included in the main directory. Start a plugin basics project with the addition of the dsp module to build.

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

Third-Party License Notices
Steinberg VST3 SDK

This software uses the VST3 Software Development Kit (SDK) by Steinberg Media Technologies GmbH.

VST is a trademark of Steinberg Media Technologies GmbH.
The VST3 SDK is licensed under the Steinberg VST3 License
VST is a trademark owned by Steinberg Media Technologies GmbH, which is based in Hamburg, Germany. The trademark was filed with the EUIPO on January 28, 2019, and covers downloadable and recorded computer plugin interface software for audio processing, transmission, recording, and playback. Additionally, VST is recognized as a registered trademark in various countries, including the U.S.A..  I am not located in Europe or the U.S.A.
Personally I may use the word VST to mean any windows based plugin and usage may not be to describe any broad catagory of computer
plugins for transmission, recording and playback - I may not in fact mean Steinberg VST plugins but rather plugins that use Steinbergs
development kits OR not as vst is now out of patent for the original patents in the 1990s in places with patent expiry periods. Not
all plugins are developed with VST SDK kids but many are in one form or another, so just to clarify if I use the term VST it may be
synonomous to the world audio plugin, it is just a personal lexicon thing  for me, as I don't generally refer to Steinberg VST SDK outside this specific context of license notices it would not lead to confusion if not for the shoehorning of the term VST to refer 
specifically to a Steinberg product as Steinberg and many other companies sell vst's but they are not Steinbergs products in general the vast majority are not which could lead to confusion as I personally consider VST to be a standard not a product.

JUCE 8 Framework

This project uses the JUCE framework, an open-source cross-platform C++ application framework for audio and GUI development.

Copyright © 2025 Raw Material Software Limited.
JUCE is licensed under the GPL v3 (free and open-source) or a commercial license for closed-source use.
See JUCE License
 for details.

