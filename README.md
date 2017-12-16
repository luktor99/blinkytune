# BlinkyTune

## Build instructions

The project makes use of the following libraries to work:

- portaudio: [Portaudio](http://www.portaudio.com/)
- kfr: [kfr](https://www.kfrlib.com/)
- Qt5: [Qt5](https://www.qt.io/)
- Boost (version >= 1.34.0) [Boost](http://www.boost.org/)

Portaudio and kfr libraries are embedded into this repository.
The other two have to be installed manually.

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
git clone https://github.com/luktor99/blinkytune.git
mkdir cmake-build
cd cmake-build
cmake -DQt5_DIR=/path/to/Qt5 ..
make
```





