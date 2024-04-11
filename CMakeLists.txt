cmake_minimum_required(VERSION 3.0)
project(hexplayer)

set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set include directory for headers
set(CMAKE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include")

# Find source files in src directory (excluding headers)
file(GLOB_RECURSE SOURCE_FILES "*.cpp" EXCLUDE PATHS "${CMAKE_CURRENT_SOURCE_DIR}/include")

# Create an executable using main.cpp and other source files
add_executable(hexplayer ${SOURCE_FILES})
