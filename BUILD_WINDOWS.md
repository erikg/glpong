# Building GLPong on Windows

## Prerequisites

### Option 1: Using vcpkg (Recommended)

1. Install vcpkg if you haven't already:
```cmd
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat
```

2. Install required packages:
```cmd
.\vcpkg install sdl2:x64-windows
.\vcpkg install libpng:x64-windows
.\vcpkg install openal-soft:x64-windows
```

3. Configure CMake with vcpkg toolchain:
```cmd
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=path\to\vcpkg\scripts\buildsystems\vcpkg.cmake
```

### Option 2: Manual Library Installation

Download and install the following libraries manually:
- SDL2 development libraries from https://www.libsdl.org/
- libpng from http://www.libpng.org/
- OpenAL Soft from https://openal-soft.org/

Then configure CMake with library paths:
```cmd
cmake -B build -S . -DSDL2_DIR=path\to\sdl2 -DPNG_ROOT=path\to\libpng
```

## Building

After configuration, build the project:
```cmd
cmake --build build --config Release
```

The executable will be created in `build\src\Release\glpong.exe`