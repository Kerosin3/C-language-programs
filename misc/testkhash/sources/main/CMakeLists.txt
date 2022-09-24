#ADD_LIBRARY( parserlib STATIC
#	     files.c 
#	     misc.c
#	     string_parse.c
#	     thrd_store.c
#	     )
ADD_EXECUTABLE (app.out
		main.c)

	#TARGET_LINK_LIBRARIES(app.out
	#		      parserlib)
