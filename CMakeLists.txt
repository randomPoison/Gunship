cmake_minimum_required(VERSION 2.8)

# Change this to your project's name
set(PROJECT_NAME "gunship")

project(${PROJECT_NAME} CXX C)

# Avoid source tree pollution
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
	message(FATAL_ERROR "In-source builds are not permitted. Make a separate folder for building:\nmkdir build; cd build; cmake ..\nBefore that, remove the files already created:\nrm -rf CMakeCache.txt CMakeFiles")
endif(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)

# Add a sensible build type default and warning because empty means no optimization and no debug info.
if(NOT CMAKE_BUILD_TYPE)
	message("WARNING: CMAKE_BUILD_TYPE is not defined!\n         Defaulting to CMAKE_BUILD_TYPE=RelWithDebInfo. Use ccmake to set a proper value.")
	set(CMAKE_BUILD_TYPE RelWithDebInfo
		CACHE STRING "Type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
		FORCE)
endif(NOT CMAKE_BUILD_TYPE)

# Include path for additional CMake library finding scripts
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# We want the binaries to be easily accessible
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# Add the libraries

# Tell SDL that we're a library, not an executable
set(SDL2_BUILDING_LIBRARY true)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
set(LIB_DIRS ${LIB_DIRS} ${SDL2_LIBRARY_DIRS})
list(APPEND LIBS ${SDL2_LIBRARY})

find_package(OGRE REQUIRED)
set(LIB_DIRS ${LIB_DIRS} ${OGRE_LIBRARY_DIRS})
set(LIB_DIRS ${LIB_DIRS} ${Boost_LIBRARY_DIR})
include_directories(${OGRE_INCLUDE_DIRS})
list(APPEND LIBS ${OGRE_LIBRARIES})

add_definitions(-DOGRE_PLUGIN_DIR_REL="${OGRE_PLUGIN_DIR_REL}")
add_definitions(-DOGRE_PLUGIN_DIR_DBG="${OGRE_PLUGIN_DIR_DBG}")

# The project's include directories
file(GLOB PROJECT_INCLUDES
	include)
include_directories(${PROJECT_INCLUDES})
set(GUNSHIP_INCLUDES ${PROJECT_INCLUDES})

# The project's sources
file(GLOB PROJECT_SOURCES
	source/*.cpp
	include/*.h)

# Now compile the library
add_library(${PROJECT_NAME} ${PROJECT_SOURCES})
