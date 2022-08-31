ADD_LIBRARY( testlib STATIC
	     mapping.c
	     )
ADD_EXECUTABLE (app.out
		main.c)

TARGET_LINK_LIBRARIES(app.out
		      testlib)
