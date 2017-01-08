============ Sources used for MSVC static libs ============

- for this prototype all static libs were compiled for 32-bit Windows systems
- for future configurations (Mac OS X or 64-bit systems) suitable static libs have to be created

  ========== libsndfile ==========
    
    - from https://github.com/lordmulder/libsndfile-MSVC
    - last access: 01.10.2016

    - provides a MSVC project solution file to build lib

    - needed for creating a temporary resampled HRIR file
    - SSR uses this to read the HRIR file data

    IMPORTANT: 
    - "#define SF_MAX_CHANNELS 256" in common.h line 113
      has to be changed to at least 720 channels due to
      writing a temporary hrir file

  ========== FFTW3 ==========

    - from http://www.fftw.org/install/windows.html
    - last access: 01.10.2016

    - using "Project files to compile FFTW 3.3 with Visual Studio 2010"
      download link: ftp://ftp.fftw.org/pub/fftw/fftw-3.3-libs-visual-studio-2010.zip
    - follow Readme.txt in zip

    - needed for the SSR's rendering algorithms

  ========== LibXML2 ==========
    
    - from http://hostagebrain.blogspot.de/search/label/libxml2
    - last access: 01.10.2016

    - needs to be build via MSVC console 
    - follow the instructions on the website

    - this is not used by the prototype (maybe in the future)
