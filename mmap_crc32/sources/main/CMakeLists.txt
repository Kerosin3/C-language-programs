ADD_LIBRARY( calc_crc32lib STATIC
	     mapping.c
	     )
ADD_EXECUTABLE (app.out
		main.c)

TARGET_LINK_LIBRARIES(app.out
		      calc_crc32lib)
