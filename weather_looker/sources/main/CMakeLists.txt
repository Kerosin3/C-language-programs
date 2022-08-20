project(main_app)


add_executable(${PROJECT_NAME} 
	main.c
)
target_include_directories(${PROJECT_NAME} 
	PUBLIC 
	"${CMAKE_CURRENT_SOURCE_DIR}/../cJSON"
	"${CMAKE_CURRENT_SOURCE_DIR}/../curl-7.84.0/include/curl"
	)

target_link_libraries( ${PROJECT_NAME}
	cjson
	libcurl
	)

