
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
    DATADIR="data"
)

# Conditional OpenAL support
if(OPENAL_FOUND)
    target_compile_definitions(glpong PRIVATE HAVE_SOUND)
endif()

# Target include directories
target_include_directories(glpong PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${SDL2_INCLUDE_DIRS}
    ${PNG_INCLUDE_DIR}
    ${OPENGL_PKG_INCLUDE_DIRS}
)

if(OPENAL_FOUND)
    target_include_directories(glpong PRIVATE ${OPENAL_INCLUDE_DIRS})
endif()

# Target link libraries
target_link_libraries(glpong PRIVATE
    ${SDL2_LIBRARIES}
    ${PNG_LIBRARY}
    ${OPENGL_PKG_LIBRARIES}
    m
)

if(OPENAL_FOUND)
    target_link_libraries(glpong PRIVATE ${OPENAL_LIBRARIES})
endif()
