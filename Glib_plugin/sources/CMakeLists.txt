cmake_minimum_required(VERSION 3.14)

project(executable)

FIND_PACKAGE(PkgConfig REQUIRED)
pkg_check_modules(GLIB REQUIRED glib-2.0)

pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0)
pkg_check_modules(GST_APP REQUIRED gstreamer-app-1.0)
pkg_check_modules(GST_VIDEO REQUIRED gstreamer-video-1.0)



include_directories (${GLIB_INCLUDE_DIRS}) #glib
include_directories (   		   #gstreamer
	${GSTREAMER_INCLUDE_DIRS}
        ${GST_APP_INCLUDE_DIRS}
	${GST_VIDEO_INCLUDE_DIRS}
	/usr/include/gstreamer-1.0/gst
	)

ADD_EXECUTABLE (app.out
		main.c
		)

LINK_DIRECTORIES(${GLIB_LIBRARY_DIRS})
LINK_DIRECTORIES(
  ${GSTREAMER_LIBRARY_DIRS}
  ${GST_APP_LIBRARY_DIRS}
  ${GST_VIDEO_LIBRARY_DIRS}
)

TARGET_LINK_LIBRARIES(app.out
		     ${GLIB_LIBRARIES}	 
		     ${GSTREAMER_LIBRARIES}
		     ${GST_APP_LIBRARIES}
		     ${GST_VIDEO_LIBRARIES}
		     #glib-2.0
		     #gstreamer-1.0
	      	     )
	     #add_definitions (${GLIB_CFLAGS_OTHER})

	     #TARGET_LINK_LIBRARIES(app.out ${GLIB_LIBRARIES})

	     #target_link_libraries(app.out ${GST_APP_LIBRARIES} ${GST_VIDEO_LIBRARIES})

