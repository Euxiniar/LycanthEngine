cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
cmake_policy(VERSION 3.1)

set (CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/Bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/Bin)

set(LIBS ${CMAKE_SOURCE_DIR}/deps/libs)
set(EXTERNALS ${CMAKE_SOURCE_DIR}/deps/externals)
set(DEPS ${CMAKE_SOURCE_DIR}/deps)

project(LycanthEngine)
add_subdirectory(deps)
add_subdirectory(sources)