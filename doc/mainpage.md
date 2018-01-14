# BlinkyTune

<p align="center">
<img src="../blinkytune_big.png">
</p>

## Project overview
BlinkyTune is a program that generates various light effects and displays them on a RGB LED strip.

## Build instructions

The project makes use of the following libraries to work:

- portaudio: [Portaudio](http://www.portaudio.com/)
- kfr: [kfr](https://www.kfrlib.com/)
- Qt5: [Qt5](https://www.qt.io/)
- Boost (version >= 1.34.0) [Boost](http://www.boost.org/)

Portaudio and kfr libraries are embedded into this repository.
The other two have to be installed in the system manually.

### Requirements:

#### Linux:

- GCC compiler supporting C++14 standard
- CMake (version >= 3.5)
- Git

#### Windows:

- Microsoft Visual C++ (version >= Visual Studio 2015 Update 2)
- CMake (version >= 3.5)
- Git

### Build process:

#### Linux:

```
git clone --recursive https://github.com/luktor99/blinkytune.git
mkdir cmake-build
cd cmake-build
cmake -DQt5_DIR=/path/to/Qt5 ..
make -j 4
```

#### Windows:

Execute these commands using Visual Studio Command Prompt:

```
git clone --recursive https://github.com/luktor99/blinkytune.git
mkdir cmake-build
cd cmake-build
cmake -G "Visual Studio 14 2015" -DQt5_DIR=C:\path\to\Qt5 ..
msbuild blinkytune.sln
```

## Documentation
Project code documentation will be generated using Doxygen.  





