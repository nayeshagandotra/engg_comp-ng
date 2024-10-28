cmake_minimum_required(VERSION 3.5)

project(ps5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)

add_subdirectory(../public/src ${CMAKE_BINARY_DIR}/public)

add_library(mmlplayer mmlplayer.h mmlplayer.cpp)

target_include_directories(mmlplayer PUBLIC .)

add_executable(ps5 MACOSX_BUNDLE demo.cpp)
target_link_libraries(ps5 fssimplewindow ysbitmapfont yssimplesound mmlplayer)
