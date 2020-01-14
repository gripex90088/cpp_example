#!/bin/bash


cd /home/debian/Cprojects/mongoose_http_message/build

if [$? -ne 0]; then
    exit
fi


rm -rf ./draw ./CMakeFiles ./CMakeCache.txt ./Makefile ./cmake_install.cmake
cmake .. && make

