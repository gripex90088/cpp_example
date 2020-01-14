cmake_minimum_required(VERSION 3.13.4)

project(redisclient)

set(PROJECT_DIR /home/debian/Cprojects/redisclient)

include_directories(/usr/local/include)

add_executable(redisclient hiredis.cpp)

add_definitions(-std=c++11 -O0 -g -W -Wall)

#target_link_libraries(redisclient pthread boost_system boost_thread)
target_link_libraries(redisclient hiredis)
