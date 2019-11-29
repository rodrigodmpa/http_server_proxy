cmake_minimum_required(VERSION 3.15)
project(http_server_proxy)

set(CMAKE_CXX_STANDARD 17)
find_package(Qt5Widgets REQUIRED)

add_executable(http_server_proxy main.cpp Client.cpp Client.h)
target_link_libraries(http_server_proxy Qt5::Widgets)