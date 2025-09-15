
# Define source files
set(GLPONG_SOURCES
    ai.c
    game.c
    image.c
    input.c
    main.c
    map.c
    physics.c
    sound.c
    text.c
    timer.c
    utils.c
    video.c
)

# Create executable target
add_executable(glpong ${GLPONG_SOURCES})

# Set target properties
set_target_properties(glpong PROPERTIES
    MACOSX_BUNDLE TRUE
    C_STANDARD 99
    C_STANDARD_REQUIRED ON
)

# Target compile definitions
target_compile_definitions(glpong PRIVATE
    PACKAGE="glpong"
    VERSION="${PROJECT_VERSION}"
)

# Platform-specific data directory
if(WIN32)
    target_compile_definitions(glpong PRIVATE
        DATADIR_RELATIVE="data"
    )
else()
    target_compile_definitions(glpong PRIVATE
        DATADIR="data"
    )
endif()

# Windows-specific compile definitions
if(WIN32)
    target_compile_definitions(glpong PRIVATE
        _CRT_SECURE_NO_WARNINGS
    )
endif()

# Conditional OpenAL support
if(WIN32)
    if(OpenAL_FOUND)
        target_compile_definitions(glpong PRIVATE HAVE_SOUND)
    endif()
else()
    if(OPENAL_FOUND)
        target_compile_definitions(glpong PRIVATE HAVE_SOUND)
    endif()
endif()

# Target include directories
target_include_directories(glpong PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PNG_INCLUDE_DIR}
)

# Platform-specific includes and libraries
if(WIN32)
    target_link_libraries(glpong PRIVATE
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
        PNG::PNG
        OpenGL::GL
    )
    if(OpenAL_FOUND)
        target_link_libraries(glpong PRIVATE OpenAL::OpenAL)
    endif()
else()
    target_include_directories(glpong PRIVATE
        ${SDL2_INCLUDE_DIRS}
        ${OPENGL_PKG_INCLUDE_DIRS}
    )
    target_link_libraries(glpong PRIVATE
        ${SDL2_LIBRARIES}
        ${PNG_LIBRARY}
        ${OPENGL_PKG_LIBRARIES}
        m
    )
    if(OPENAL_FOUND)
        target_include_directories(glpong PRIVATE ${OPENAL_INCLUDE_DIRS})
        target_link_libraries(glpong PRIVATE ${OPENAL_LIBRARIES})
    endif()
endif()
