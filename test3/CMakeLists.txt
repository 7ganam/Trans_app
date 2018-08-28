# Specify the minimum version for CMake

cmake_minimum_required(VERSION 2.8)

# Project's name
project(trans_app)


set(CMAKE_CXX_STANDARD 11)  # for c++11

find_package(X11 REQUIRED)
link_libraries(${X11_LIBRARIES})
include_directories(${X11_INCLUDE_DIR})



add_executable(app1 app1.cpp)


# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# The following folder will be included
include_directories("${PROJECT_SOURCE_DIR}") 

#add the tinyxml_library by adding the cmakelists file in tinyxml_library directory
include_directories ("${PROJECT_SOURCE_DIR}/tinyxml_library")
add_subdirectory (tinyxml_library)

include_directories ("${PROJECT_SOURCE_DIR}/get_pointer_library")
  add_subdirectory (get_pointer_library)


find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
link_libraries(${OpenCV_LIBRARIES})

target_link_libraries( app1 ${OpenCV_LIBS} ${TINY_XML_LIB} ${GET_POINTER}) 
