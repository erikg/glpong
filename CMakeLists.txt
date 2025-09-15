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
find_package(PNG REQUIRED)
find_package(OpenGL REQUIRED)

# Platform-specific package finding
if(WIN32)
    # On Windows, use vcpkg or manual paths
    find_package(SDL2 REQUIRED)
    find_package(OpenAL CONFIG)
else()
    # On Unix-like systems, use pkg-config
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SDL2 REQUIRED sdl2)
    pkg_check_modules(OPENAL openal)
endif()

add_subdirectory(src)

# Install executable and data files
if(WIN32)
    install(TARGETS glpong
        RUNTIME DESTINATION .
        COMPONENT Runtime)

    install(DIRECTORY data/
        DESTINATION data
        COMPONENT Runtime
        FILES_MATCHING PATTERN "*.png" PATTERN "*.wav" PATTERN "*.ico")

    # Install vcpkg DLLs
    if(CMAKE_TOOLCHAIN_FILE MATCHES "vcpkg")
        file(GLOB VCPKG_DLLS "${CMAKE_CURRENT_BINARY_DIR}/src/Release/*.dll")
        install(FILES ${VCPKG_DLLS}
            DESTINATION .
            COMPONENT Runtime)
    endif()

    # Install runtime libraries
    set(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_SKIP TRUE)
    include(InstallRequiredSystemLibraries)
    install(PROGRAMS ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS}
        DESTINATION .
        COMPONENT Runtime)
endif()

# CPack configuration
set(CPACK_PACKAGE_NAME "GLPong")
set(CPACK_PACKAGE_VENDOR "Erik Greenwald")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "OpenGL/SDL Pong Game")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "GLPong")
set(CPACK_PACKAGE_EXECUTABLES "glpong;GLPong Game")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/COPYING")

if(WIN32)
    set(CPACK_GENERATOR "NSIS")
    set(CPACK_NSIS_DISPLAY_NAME "GLPong ${PROJECT_VERSION}")
    set(CPACK_NSIS_PACKAGE_NAME "GLPong")
    set(CPACK_NSIS_CONTACT "erik@elfga.com")
    set(CPACK_NSIS_URL_INFO_ABOUT "https://github.com/elfga/glpong")
    set(CPACK_NSIS_HELP_LINK "https://github.com/elfga/glpong")
    set(CPACK_NSIS_MODIFY_PATH ON)
    set(CPACK_NSIS_MUI_ICON "${CMAKE_SOURCE_DIR}/data/paddle.ico")
    set(CPACK_NSIS_MUI_UNICON "${CMAKE_SOURCE_DIR}/data/paddle.ico")
    set(CPACK_NSIS_CREATE_ICONS_EXTRA
        "CreateShortCut '$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\GLPong.lnk' '$INSTDIR\\\\glpong.exe' '' '$INSTDIR\\\\data\\\\paddle.ico'")
    set(CPACK_NSIS_DELETE_ICONS_EXTRA
        "Delete '$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\GLPong.lnk'")
endif()

include(CPack)
