cmake_minimum_required(VERSION 3.10)

# Set default build type before project()
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build" FORCE)
endif()

project(glpong
    VERSION 1.4
    DESCRIPTION "OpenGL/SDL Pong Game"
    LANGUAGES C)

# Modern OpenGL preference
set(OpenGL_GL_PREFERENCE GLVND)

# Find required packages
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)
find_package(PNG REQUIRED)

# Try modern OpenGL first, fallback to legacy
pkg_check_modules(OPENGL_PKG opengl)
if(NOT OPENGL_PKG_FOUND)
    pkg_check_modules(OPENGL_PKG gl REQUIRED)
endif()

# Optional OpenAL
pkg_check_modules(OPENAL openal)

add_subdirectory(src)
