cmake_minimum_required(VERSION 3.13)
project(mongoose_http_message)

set(PROJECT_DIR /home/debian/Cprojects/mongoose_http_message)

include_directories(${PROJECT_DIR}/mongoose)
include_directories(${PROJECT_DIR}/logger)

aux_source_directory(${PROJECT_DIR}/mongoose MONGOOSE_SOURCE_FILES)
aux_source_directory(${PROJECT_DIR}/logger LOGGER_FILES)
set(CMAKE_CXX_STANDARD 14)

add_executable(mongoose_http_message main.cpp ${MONGOOSE_SOURCE_FILES} ${LOGGER_FILES} curl_http_request.cpp curl.cpp shareMemory.cpp)

target_link_libraries(mongoose_http_message curl
    ssl crypto curl alibabacloud-oss-cpp-sdk pthread
)
