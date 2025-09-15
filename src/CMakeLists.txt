
ADD_EXECUTABLE(glpong
	MACOSX_BUNDLE
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
	video.c)

TARGET_LINK_LIBRARIES(glpong ${OPENGL_PKG_LIBRARIES} ${SDL2_LIBRARIES} ${PNG_LIBRARY} ${SND_LIB} m)
