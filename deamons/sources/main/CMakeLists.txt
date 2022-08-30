ADD_LIBRARY( deamonmLib STATIC
	     deamonize.c
	     deamon_magic.c
	     parse_settings.c 
	     jzon.c
	     )
ADD_EXECUTABLE (deamon_app.out
		main.c)

TARGET_LINK_LIBRARIES(deamon_app.out
		     deamonmLib)
