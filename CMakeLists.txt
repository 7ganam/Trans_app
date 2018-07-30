# Specify the minimum version for CMake

cmake_minimum_required(VERSION 2.8)

# Project's name
project(trans_app)


set(CMAKE_CXX_STANDARD 11)  # for c++11

find_package(X11 REQUIRED)
link_libraries(${X11_LIBRARIES})
include_directories(${X11_INCLUDE_DIR})


add_executable(screen_shot screen_shot.cpp)
add_executable(get_screen_size get_screen_size.cpp)



# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
# The following folder will be included
include_directories("${PROJECT_SOURCE_DIR}") 



find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
target_link_libraries( screen_shot ${OpenCV_LIBS} ) 

