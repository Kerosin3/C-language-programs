project(main_app)

#set(CURL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../curl-7.84.0)
#find_package(CURL REQUIRED)

add_executable(${PROJECT_NAME}
	main.c
)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../curl-7.84.0/include/curl)

#link_directories(${CMAKE_BINARY_DIR})
find_library(curl_lib curl)
target_link_libraries( ${PROJECT_NAME}
	PRIVATE
	"${curl_lib}"
	#	${CMAKE_BINARY_DIR}/libcurl.a
	)
#add_custom_command(TARGET app_complete.out
#                   POST_BUILD
#                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:MyExe> SomeOtherDir)

message(======= ${CMAKE_BINARY_DIR})
add_custom_target( FinalMessage ALL
    ${CMAKE_COMMAND} -E cmake_echo_color --cyan "Compilation is over!"
    COMMENT "-------------------executable has been putted in test directory----------------------------" )
add_dependencies( FinalMessage main_app)
