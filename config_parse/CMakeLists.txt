cmake_minimum_required (VERSION 3.10.2)

project (configParser)

set(HOMEPATH /home/xuxing/projects/cpp_example/config_parse)
# 版本号
set (configPraser_VERSION_MAJOR 1)

#include_directories(${HOMEPATH}/)
include_directories(${HOMEPATH}/src ${HOMEPATH}/inc)
#include_directories(${HOMEPATH}/src)

add_definitions (-std=c++11  -g -Wall)

add_executable (${PROJECT_NAME} 
	./src/main.cpp
	./inc/parse_conf.h
	./src/parse_conf.cpp
	./inc/qstring.h
	./src/qstring.cpp
)