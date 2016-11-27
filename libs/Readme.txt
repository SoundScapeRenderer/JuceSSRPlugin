============ Sources used for MSVC static libs ============

  ========== LibSndFile ==========
    
    - from https://github.com/lordmulder/libsndfile-MSVC
    - last access: 01.10.2016

    - provides MSVC project solution file to build lib

    NOTE: 
    - "#define SF_MAX_CHANNELS 256" in common.h line 113
      has to be changed to at least 720 channels due to
      writing a temporary hrir file

  ========== FFTW3 ==========

    - from http://www.fftw.org/install/windows.html
    - last access: 01.10.2016

    - using "Project files to compile FFTW 3.3 with Visual Studio 2010"
      download link: ftp://ftp.fftw.org/pub/fftw/fftw-3.3-libs-visual-studio-2010.zip
    - follow Readme.txt in zip
    