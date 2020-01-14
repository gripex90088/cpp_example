cmake_minimum_required(VERSION 3.10.2)

project(fileio)

#set($HOMEPATH /home/xuxing/projects/cpp_example/linux_unix_programming_manual/)

include_directories(/home/xuxing/projects/cpp_example/linux_unix_programming_manual/lib)

add_executable(
	fileio
	../lib/tlpi_hdr.h
	../lib/error_functions.h
	../lib/error_functions.c
	../lib/get_num.h
	../lib/get_num.c
	./bad_exclusive_open.c
)