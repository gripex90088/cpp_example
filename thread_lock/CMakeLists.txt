cmake_minimum_required(VERSION 3.13.4)
project(thread_lock)

set(CMAKE_CXX_STANDARD 14)

add_executable(thread_lock main.cpp)

target_link_libraries(thread_lock pthread)