cmake_minimum_required(VERSION 3.14)

project(executable)

FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GLIB REQUIRED glib-2.0)
LINK_DIRECTORIES(${GLIB_LIBRARY_DIRS})

ADD_EXECUTABLE (app.out
		main.c
		)
include_directories (${GLIB_INCLUDE_DIRS})
link_directories (${GGLIB_LIBRARY_DIRS})

TARGET_LINK_LIBRARIES(app.out
		     glib-2.0
	      	     )
	     add_definitions (${GLIB_CFLAGS_OTHER})
TARGET_LINK_LIBRARIES(app.out ${GLIB_LIBRARIES})
