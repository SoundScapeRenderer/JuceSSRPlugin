# General Information

This is the source distribution of the JuceSSRPlugin. The aim of the JuceSSRPlugin is to realise the [SoundScape Renderer \(SSR\)](http://spatialaudio.net/ssr/) as an autonomous cross-platform audio plug-in. This way, the SSR reaches a wider audience than it can through the native application.

Note that the JuceSSRPlugin is still a **prototype**. While not every feature and characteristic of the SoundScape Renderer could be realised, new useful ones were introduced. As for now, only the simple binaural synthesis of the SSR without headtracking is supported.

Since the audio plug-in environment differs inherently from that of a native application, this plug-in could not just be wrapped around the SoundScape Renderer code. Instead, the SSR is used as a C++ library.

Parts of the JuceSSRPlugin code comes from the open-source synthesizer [Synister](https://the-synister.github.io/).

# Compilation

The JuceSSRPlugin uses the [JUCE](https://www.juce.com/) framework. For the prototype only a 32-bit VST plug-in configuration for Microsoft Visual Studio 15 was created. Via JUCE further configurations can be added easily.

### Requirements

- Windows PC with **Microsoft Visual Studio 15** (other versions may be possible, not sure though)
- Steinberg's **VST SDK**, the current VST3 SDK can be downloaded from [here](https://www.steinberg.net/de/company/developer.html)

### Build in Visual Studio

1. Clone the JuceSSRPlugin repository from here:
https://github.com/SoundScapeRenderer/JuceSSRPlugin.
2. Make sure the VST SDK folder is named "VST SDK" and it is located in **C:/**. If needed, within JUCE's Introjucer the path to the VST SDK folder can be changed.
3. Open **JuceSSRPlugin/plugin/Builds/VisualStudio15/plugin.vcxproj** in Visual Studio.
4. Build the project map \(ctrl+shift+b\).

# Licence

The JuceSSRPlugin is licenced under the GNU GENERAL PUBLIC LICENSE.

Copyright © 2016
[Quality and Usability Lab Berlin Institute of Technology](http://www.qu.tu-berlin.de/)