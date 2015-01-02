cmake_minimum_required(VERSION 2.8.12)

include(ExternalProject)

function(source_group_setup ALL_FILES)
	foreach(FILE ${ALL_FILES})
		get_filename_component(PARENT_DIR "${FILE}" PATH)

		# skip src or include and changes /'s to \\'s
		string(REGEX REPLACE "(\\./)?(src|include)/?" "" GROUP "${PARENT_DIR}")
		string(REPLACE "/" "\\" GROUP "${GROUP}")

		# group into "Source Files" and "Header Files"
		if ("${FILE}" MATCHES ".*\\.cpp")
			set(GROUP "Source Files\\${GROUP}")
		elseif("${FILE}" MATCHES ".*\\.h")
			set(GROUP "Header Files\\${GROUP}")
		endif()

		source_group("${GROUP}" FILES "${FILE}")
	endforeach()
endfunction(source_group_setup)

project(Gunship CXX C)

# Avoid source tree pollution
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
	message(FATAL_ERROR "In-source builds are not permitted. Make a separate folder for building:\nmkdir build; cd build; cmake ..\nBefore that, remove the files already created:\nrm -rf CMakeCache.txt CMakeFiles")
endif(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)

# Add a sensible build type default and warning because empty means no optimization and no debug info.
if(NOT CMAKE_BUILD_TYPE)
	message("WARNING: CMAKE_BUILD_TYPE is not defined!\n         Defaulting to CMAKE_BUILD_TYPE=Debug. Use ccmake to set a proper value.")
	set(CMAKE_BUILD_TYPE Debug
	    CACHE STRING "Type of build, options are: None Debug Release RelWithDebInfo."
	    FORCE)
endif(NOT CMAKE_BUILD_TYPE)

set(GUNSHIP_BUILD_EXE ON
    CACHE BOOL "Whether or not Gunship should build the default executable. If OFF, only the static library will be built.")

# Include path for additional CMake library finding scripts
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(SDL2_BUILDING_LIBRARY true)
find_package(SDL2 REQUIRED)
list(APPEND LIBS ${SDL2_LIBRARY})

find_package(OGRE REQUIRED)
list(APPEND LIBS ${OGRE_LIBRARIES})

add_definitions(-DOGRE_PLUGIN_DIR_REL="${OGRE_PLUGIN_DIR_REL}")
add_definitions(-DOGRE_PLUGIN_DIR_DBG="${OGRE_PLUGIN_DIR_DBG}")

# The project's include directories
set(GUNSHIP_EXTERNAL_INCLUDES
    ${SDL2_INCLUDE_DIR}
    ${OGRE_INCLUDE_DIRS})

set(GUNSHIP_INCLUDE_DIR
    include)

set(GUNSHIP_INCLUDE_DIRS
    ${GUNSHIP_INCLUDE_DIR}
    ${GUNSHIP_EXTERNAL_INCLUDES})

# Get all source files (used for setting up VS filters)
file(GLOB_RECURSE PROJECT_SOURCES
     source/*.cpp)

file(GLOB GUNSHIP_EXE_SOURCES
     source/Gunship.cpp)

# All header files (used for setting up VS filters)
file(GLOB_RECURSE PROJECT_INCLUDES
     include/*.h)

# Get source files for libgunship (PROJECT_SOURCES minus Gunship.cpp)
set(LIBGUNSHIP_SOURCES ${PROJECT_SOURCES} ${PROJECT_INCLUDES})
list(REMOVE_ITEM LIBGUNSHIP_SOURCES ${GUNSHIP_EXE_SOURCES})

# setup VS filters (and I guess it also does something for XCode?)
source_group_setup(PROJECT_SORCES)
source_group_setup(PROJECT_INCLUDES)

# Create static library target
add_library(LibGunship STATIC ${LIBGUNSHIP_SOURCES})
add_dependencies(LibGunship entityx)
target_link_libraries(LibGunship ${LIBS})
target_include_directories(LibGunship PUBLIC ${GUNSHIP_INCLUDE_DIR})
target_include_directories(LibGunship SYSTEM PUBLIC ${GUNSHIP_EXTERNAL_INCLUDES})

# Now create the default executable
if(${GUNSHIP_BUILD_EXE})
	add_executable(Gunship ${GUNSHIP_EXE_SOURCES})
	target_link_libraries(Gunship LibGunship)
endif(${GUNSHIP_BUILD_EXE})

# Compiler flags
if (CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-unused-parameter -std=c++11")
endif(CMAKE_COMPILER_IS_GNUCXX)
