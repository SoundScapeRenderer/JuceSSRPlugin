# General Information

This is the source distribution of the JuceSSRPlugin. The aim of the JuceSSRPlugin is to realise the [SoundScape Renderer (SSR)](http://spatialaudio.net/ssr/) as an autonomous cross-platform audio effects plug-in. This way, the SSR reaches a wider audience than it can through the native application.

Note that the JuceSSRPlugin is still a **prototype**. While not every feature and characteristic of the SoundScape Renderer could be realised, new useful ones were introduced. As for now, only the simple binaural synthesis of the SSR without headtracking is supported.

Since the audio plug-in environment differs inherently from that of a native application, this plug-in could not just be wrapped around the SoundScape Renderer code. Instead, the SSR is used as a C++ library.

Parts of the JuceSSRPlugin code comes from the open-source synthesizer [Synister](https://the-synister.github.io/).

# Differences compared to the SoundScape Renderer

#### OS and Host Compability

As a 32-bit system VST plug-in, the host support of the JuceSSRPlugin prototype may still be limited. Nevertheless, the JuceSSRPlugin has been successfully tested in 32-bit system versions of Cubase, Live, Reaper and FL Studio on Windows. Other versions are planned though to make this prototype compatible with Mac OS X systems and 64-bit system DAWs.

#### Implemented Rendering Algorithms

Only binaural synthesis as rendering algorithm is supported in this prototype. Hopefully soon all rendering algorithms of the SoundScape Renderer can be used in this plug-in.

#### Graphical User Interface

The plug-in GUI is based on the SoundScape Renderer with some changes. A dedicated settings window for more global configurations was added as well.

#### Number of Sound Sources

Only one sound source per plug-in can be controlled and processed. This works great for now but it would be more convenient to control all sources within the UI of each JuceSSRPlugin instance. Instead of routing many audio inputs from several host tracks into one plug-in (which is only possible in newer JUCE versions by the way), perhaps merely the source parameters need to be shared between these plug-in instances.

#### Serialization File Format

Serialization of the sound source parameters does not use the SSR's ASDF file format but an own patch file format since the JuceSSRPlugin works on a set of different parameters. The usage of the ASDF file format may still be considered for a future release though.

#### No Short-cut Keys

The SoundScape Renderer's short-cut keys were not considered because those can lead to unpredictable behaviour due to not knowing whether the DAW or the audio plug-in has the keyboard focus.

#### Resampling of the HRIR file

The binaural synthesis can be used with other sample rates than 44.1 kHz. For that, the plug-in uses via [SoX](http://sox.sourceforge.net/SoX/Resampling) pre-resampled HRIRs of the SSR's original "hrirs_fabian.wav" if possible. JUCE's LagrangeInterpolator for resampling is used otherwise. It is advised not to use the JuceSSRPlugin with sample rates that require resampling with too small or too big ratio though since JUCE's algorithm can lead to incorrect rendering.

#### Parameter Automation
Unlike the SoundScape Renderer, automation of sound source parameters is possible in the JuceSSRPlugin although some DAWs display the parameter as a number in a range of [0 ... 1] instead of the actual values used in the SSR.

# Compilation

The JuceSSRPlugin uses the [JUCE](https://www.juce.com/) framework. For the prototype only a 32-bit VST plug-in configuration for Microsoft Visual Studio 15 was created. Via JUCE further configurations can be added easily. This does not mean that these new configurations will compile just fine because the source code may contain OS specific lines. Furthermore, the linked static libraries of FFTW3 and libsndfile needed by the plug-in for using the SSR have to be adjusted then.

### Requirements

- Windows PC with **Microsoft Visual Studio 15** (other versions may be possible, not tested yet)
- Steinberg's **VST SDK**, the current VST3 SDK can be downloaded from [here](https://www.steinberg.net/de/company/developer.html)

### Build in Visual Studio

1. Clone the JuceSSRPlugin repository from here:
https://github.com/SoundScapeRenderer/JuceSSRPlugin.
2. Make sure the VST SDK folder is named "VST SDK" and it is located in **C:/**. If needed, within JUCE's Introjucer the path to the VST SDK folder can be changed.
3. Open **JuceSSRPlugin/plugin/Builds/VisualStudio15/plugin.vcxproj** in Visual Studio.
4. Build the project map (ctrl+shift+b).

If done correctly, the VST plug-in will be in the folder in which the compiled files will be created.

# Licence

The JuceSSRPlugin is licenced under the GNU GENERAL PUBLIC LICENSE.

Copyright © 2016
[Quality and Usability Lab Berlin Institute of Technology](http://www.qu.tu-berlin.de/)