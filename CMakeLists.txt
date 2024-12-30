cmake_minimum_required(VERSION 3.5)
project(hexplayer)

# set(CMAKE_CXX_COMPILER "/usr/bin/clang++")  # Optional compiler specification
set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set include directory for headers
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

# Set include directory for headers
# set(CMAKE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include")

# Modify to explicitly set the source directory (if src has a different name, adjust accordingly)
set(CMAKE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

# Find source files in src directory (excluding headers)
file(GLOB_RECURSE SOURCE_FILES "${CMAKE_SOURCE_DIR}/*.cpp")

# Add main.cpp to the source files
list(APPEND SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")

# Create an executable using the source files
add_executable(hexplayer ${SOURCE_FILES})

# Install the executable to /bin
install(TARGETS hexplayer
        DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin
        PERMISSIONS OWNER_EXECUTE OWNER_READ OWNER_WRITE GROUP_EXECUTE GROUP_READ WORLD_EXECUTE WORLD_READ)
