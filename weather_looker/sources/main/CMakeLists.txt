add_executable(app_complete.out
	main.c
)
target_link_libraries( app_complete.out
	CURL
	${PROJECT_SOURCE_DIR}/sources/libs/libspookyhash.a
	)
#add_custom_command(TARGET app_complete.out
#                   POST_BUILD
#                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:MyExe> SomeOtherDir)

add_custom_target( FinalMessage ALL
    ${CMAKE_COMMAND} -E cmake_echo_color --cyan "Compilation is over!"
    COMMENT "-------------------executable has been putted in test directory----------------------------" )
add_dependencies( FinalMessage app_complete.out )
