cmake_minimum_required(VERSION 2.8)
project( Dijkstra )

# set compiler
set( CMAKE_CXX_COMPILER "g++")

# Set the directory of binaries
set( EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin) 

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB SOURCES "src/*.cpp")
add_executable( dijkstra_heap ${SOURCES} )
