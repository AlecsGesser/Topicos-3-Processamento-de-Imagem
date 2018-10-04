cmake_minimum_required(VERSION 2.8)
project( tr2 )

set(CMAKE_CXX_FLAGS "-g -ggdb -Wall -fpermissive")
#set(CMAKE_CXX_FLAGS "-O3")


find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )


add_executable(tr2 src/main.cpp)
target_link_libraries( tr2 ${OpenCV_LIBS} )
target_link_libraries( tr2 lb_image )
target_link_libraries( tr2 lb_functions)

add_library(lb_image src/Image.cpp)

add_library(lb_functions src/functions.cpp)









