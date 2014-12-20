cmake_minimum_required(VERSION 2.8.11)

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

# Add the libraries

set(entityx_DIR "${CMAKE_SOURCE_DIR}/external/entityx")
set(entityx_INCLUDE_DIR "${entityx_DIR}/include")
set(entityx_LIBRARY "${entityx_DIR}/lib/libentityx.a")
ExternalProject_Add(entityx
                    PREFIX ${entityx_DIR}
                    GIT_REPOSITORY https://github.com/excaliburHisSheath/entityx.git
                    INSTALL_DIR ${entityx_DIR}
                    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${entityx_DIR} -DENTITYX_DT_TYPE=float
)
list(APPEND LIBS ${entityx_LIBRARY})

# Tell SDL that we're a library, not an executable
set(SDL2_BUILDING_LIBRARY true)

find_package(SDL2 REQUIRED)
list(APPEND LIBS ${SDL2_LIBRARY})

find_package(OGRE REQUIRED)
list(APPEND LIBS ${OGRE_LIBRARIES})

add_definitions(-DOGRE_PLUGIN_DIR_REL="${OGRE_PLUGIN_DIR_REL}")
add_definitions(-DOGRE_PLUGIN_DIR_DBG="${OGRE_PLUGIN_DIR_DBG}")

# The project's include directories
set(GUNSHIP_INCLUDES
    include
    ${SDL2_INCLUDE_DIR}
    ${OGRE_INCLUDE_DIRS}
    ${entityx_INCLUDE_DIR})

# The project's sources
# broken up by directory to get the filters right in VS
file(GLOB PROJECT_SOURCES
     source/*.cpp
     source/Components/*.cpp)
source_group("source" FILES ${PROJECT_SOURCES})

file(GLOB PROJECT_INCLUDES
     include/*.h
     include/Components/*.h)
source_group("include" FILES ${PROJECT_INCLUDES})

# add js file definition
add_definitions(-DJS_ROOT_DIR="${CMAKE_SOURCE_DIR}/js")

# setup VS filters (and I guess it also does something for XCode?)
source_group_setup(PROJECT_SORCES)
source_group_setup(PROJECT_INCLUDES)

# Now compile the library
add_executable(${PROJECT_NAME}
               ${PROJECT_INCLUDES} ${PROJECT_SOURCES})
target_link_libraries(${PROJECT_NAME} ${LIBS})
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ${GUNSHIP_INCLUDES})

if (CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")
endif(CMAKE_COMPILER_IS_GNUCXX)
