# Creating a Windows Installer for GLPong

This guide explains how to create a Windows installer (.exe) for GLPong.

## Prerequisites

### 1. Install NSIS (Nullsoft Scriptable Install System)

Download and install NSIS from: https://nsis.sourceforge.io/Download

Or using Chocolatey:
```cmd
choco install nsis
```

Or using Winget:
```cmd
winget install NSIS.NSIS
```

### 2. Ensure GLPong is built

Make sure you've already built GLPong following the BUILD_WINDOWS.md instructions.

## Creating the Installer

### Method 1: Using CPack (Recommended)

1. Open a command prompt in the GLPong directory
2. Reconfigure CMake to include CPack settings:
```cmd
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE="../vcpkg/scripts/buildsystems/vcpkg.cmake"
```

3. Build the project:
```cmd
cmake --build build --config Release
```

4. Create the installer:
```cmd
cd build
cpack -G NSIS
```

This will create a file named `GLPong-1.4-win64.exe` (or similar) in the build directory.

### Method 2: Manual ZIP Package

If NSIS is not available, you can create a ZIP package:

```cmd
cd build
cpack -G ZIP
```

This creates a ZIP file that users can extract and run.

## Installer Features

The created installer will:
- Install GLPong executable
- Install all required data files (textures, sounds)
- Install necessary DLL dependencies (SDL2, OpenGL, PNG, etc.)
- Create Start Menu shortcuts
- Add uninstall capability
- Optionally add to Windows PATH

## Testing the Installer

1. Run the generated .exe file
2. Follow the installation wizard
3. Verify the game launches from the Start Menu
4. Test the uninstaller from Control Panel

## Troubleshooting

- **NSIS not found**: Make sure NSIS is installed and added to PATH
- **Missing DLLs**: Verify vcpkg libraries are properly built
- **Permission errors**: Run as administrator if needed