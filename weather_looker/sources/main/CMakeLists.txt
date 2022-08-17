project(main_app)

#set(CURL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../curl-7.84.0)
#find_package(CURL REQUIRED)

add_executable(${PROJECT_NAME} 
	main.c
)
target_include_directories(${PROJECT_NAME} 
	PUBLIC 
	"${CMAKE_CURRENT_SOURCE_DIR}/../cJSON"
	#"${CMAKE_CURRENT_SOURCE_DIR}/../curl-7.84.0/include/curl"
	)

#link_directories(${CMAKE_BINARY_DIR})
find_library(curl_lib 
	    libcurl.a
	    PATH ${CMAKE_SOURCE_DIR}/sources/libs 
	    NO_DEFAULT_PATH
	    )
message(CMAKE_SOURCEDIR IS ${CMAKE_SOURCE_DIR})
message(FATAL_ERROR "${curl_lib}")


#find_library(cjsonlibrary 
#	NAMES cJSON cjson 
#	HINTS ${CMAKE_SOURCE_DIR}
#
#	)

message(CURRENTSOURCE_DIR IS ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries( ${PROJECT_NAME}
	cjson
	curl
	#"${curl_lib}"
	#"${cjsonlibrary}"
	#${CMAKE_BINARY_DIR}/libcurl.a  #link with static
	)


message(======= ${CMAKE_BINARY_DIR})
add_custom_target( FinalMessage ALL
    ${CMAKE_COMMAND} -E cmake_echo_color --cyan "Compilation is over!"
    COMMENT "-------------------executable has been putted in test directory----------------------------" )
add_dependencies( FinalMessage main_app)
