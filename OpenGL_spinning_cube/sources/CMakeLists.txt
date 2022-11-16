cmake_minimum_required(VERSION 3.14)


ADD_EXECUTABLE (spinning_cube.out
		main.c
		)

TARGET_LINK_LIBRARIES(spinning_cube.out
			GL
			GLU
			glut
	      	     )
