# CMake mim version 
# [CMake 最低版本号要求]
cmake_minimum_required (VERSION 3.2)
set(HOMEPATh /home/xuxing/projects/linux_one_cpp)

# Project information 
# [项目信息]
project (socketServer)

# find directories all source file and preservation to DIR_SRCS 
# [查找目录下的所有源文件 并将名称保存到 DIR_SRCS 变量]
# aux_source_directory(. DIR_SRCS)
# add_executable(socketServer ${DIR_SRCS})

# Add son directories
# [添加 path 子目录]
# add_subdirectory(path)

# include directories
include_directories(/home/xuxing/projects/linux_one_cpp/inc)

add_definitions(-std=c++11)


# [Specify a build target]
# [指定生成目标]
add_executable(socketServer linux_one_cpp.cpp mysock.cpp)

# Add link library
# [添加链接库]
# target_link_libraries(socketServer lib_name)


