cmake_minimum_required(VERSION 2.8.4)
project(SyscallRead)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -D_FILE_OFFSET_BITS=64")

set(SOURCE_FILES main.cpp)
add_executable(SyscallRead ${SOURCE_FILES})