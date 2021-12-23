cmake_minimum_required(VERSION 3.21)
project(DataTransfer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-std=gnu++2a -Wall -Werror -Wpedantic -pthread")
#set(CMAKE_CXX_COMPILER           "/usr/bin/gcc-10.exe")

add_executable(DataTransfer main.cpp requests.h http_req.hpp)

find_package(fmt)
#find_package(nlohmann_json 3.2.0 REQUIRED)

target_link_libraries(DataTransfer fmt::fmt)
#target_link_libraries(DataTransfer PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(DataTransfer mysqlcppconn)