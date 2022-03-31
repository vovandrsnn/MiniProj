cmake_minimum_required(VERSION 3.16)
project(mini_proj)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenCV REQUIRED)

add_executable(mini_proj cmd.cpp cmd.hpp imagefunc.cpp image.hpp main.cpp)
set_property(TARGET mini_proj PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "/usr/include/opencv4")
target_link_libraries(mini_proj ${OpenCV_LIBS})
