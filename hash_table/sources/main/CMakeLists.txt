add_executable(app_complete.out
	main.c
)
target_link_libraries( app_complete.out
	side
	${PROJECT_SOURCE_DIR}/sources/libs/libspookyhash.a
	)
#add_custom_command(TARGET app_complete.out
#                   POST_BUILD
#                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:MyExe> SomeOtherDir)
