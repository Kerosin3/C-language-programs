cmake_minimum_required(VERSION 3.14)

project(hash_table LANGUAGES C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_C_FLAGS "-Wall -Wextra -Wpedantic -pedantic-errors")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/../test)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_PATH}/output/${CMAKE_BUILD_TYPE})
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_PATH}/output)
#add_custom_command(TARGET ${PROJECT_NAME}
#    PRE_BUILD
    #COMMAND make -f ${CMAKE_PROJECT_DIR}/sources/shookyhash/Makefile
    #    COMMAND cd ${CMAKE_PROJECT_DIR}/sources/spookyhash/build
    #COMMAND premake gmake
    #COMMAND make -f ${CMAKE_PROJECT_DIR}/sources/shookyhash/Makefile
    #)
add_custom_target(
    build_spookyhash ALL
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/sources/spookyhash/build
    COMMAND premake5 gmake
    COMMAND make -f Makefile
    COMMAND cp bin/Release/libspookyhash.a ${PROJECT_SOURCE_DIR}/sources/libs
    COMMENT "===========compiled spookyhash lib============="
    VERBATIM
)
#add_dependencies(hash_table build_spookyhash)

add_subdirectory(sources/main)
add_subdirectory(sources/side)

#add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#                   COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --cyan
#                   "Message after yourtarget has been built.")
