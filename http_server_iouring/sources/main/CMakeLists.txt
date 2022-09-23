ADD_LIBRARY( servapplib STATIC
	     bufandfiles.c
	     event_loop.c
	     misc.c
	     setup.c
	     connection_handlers.c
	     response_parser.c
	     )

TARGET_LINK_LIBRARIES( servapplib 
	picohttpparserlib
	)

ADD_EXECUTABLE (app.out
		main.c)

TARGET_LINK_LIBRARIES(app.out
		      picohttpparserlib
		      servapplib
		      uring
		      )
