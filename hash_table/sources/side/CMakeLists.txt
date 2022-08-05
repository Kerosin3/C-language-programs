add_library(
	side
	hash_f.c
	misc.c
	)
target_include_directories(side PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
