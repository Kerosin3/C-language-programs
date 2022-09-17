ADD_LIBRARY( dbg_loggerlib STATIC
	     debug_logger.c
	     )
ADD_EXECUTABLE (app.out
		main.c)

TARGET_LINK_LIBRARIES(app.out
		      dbg_loggerlib
		      )
