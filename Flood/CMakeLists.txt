cmake_minimum_required(VERSION 2.8)
project( Flood )

set(CMAKE_CXX_FLAGS "-g -ggdb -Wall -fpermissive")
#set(CMAKE_CXX_FLAGS "-O3")

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )



add_executable(segmenta src/main.cpp)

target_link_libraries( segmenta ${OpenCV_LIBS} )

target_link_libraries( segmenta lb_flood )

add_library(lb_flood src/Flood.cpp)

target_link_libraries( lb_flood ${OpenCV_LIBS} )
