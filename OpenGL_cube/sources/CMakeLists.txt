cmake_minimum_required(VERSION 3.14)


ADD_EXECUTABLE (app.out
		main.c
		cube.c
		)

TARGET_LINK_LIBRARIES(app.out
			GL
			GLU
			glut
	      	     )
