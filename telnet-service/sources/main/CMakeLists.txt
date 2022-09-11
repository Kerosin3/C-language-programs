ADD_LIBRARY( telnetservicelib STATIC
	     )
ADD_EXECUTABLE (app.out
		main.c)

TARGET_LINK_LIBRARIES(app.out
		      telnetservice)
