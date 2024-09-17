cmake_minimum_required(VERSION 3.5)

project(ps3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)

add_library(fssimplewindow fssimplewindow.h fssimplewindowcpp.cpp)
target_include_directories(fssimplewindow PUBLIC .)


add_executable(ps3-2 MACOSX_BUNDLE ps3-2.cpp)
target_link_libraries(ps3-2 fssimplewindow)
