cmake_minimum_required(VERSION 3.10)
project(MyProject C)

set(CMAKE_GENERATOR "MinGW Makefiles")
set(CMAKE_C_STANDARD 90)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wsign-conversion -Wconversion -pedantic")

set(SRC_DIR src)
set(BUILD_DIR build)

file(GLOB SRCS "${SRC_DIR}/*.c")

foreach(src_file ${SRCS})
    get_filename_component(exe_name ${src_file} NAME_WE)
    add_executable(${exe_name} ${src_file})
    set_target_properties(${exe_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR})
endforeach()
