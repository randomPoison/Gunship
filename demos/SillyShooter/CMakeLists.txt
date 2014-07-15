cmake_minimum_required (VERSION 3.0)

# Set project name
set (PROJECT_NAME "SillyShooter")

project (${PROJECT_NAME} CXX C)

# Avoid source tree pollution
if (CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
	message (FATAL_ERROR "In-source builds are not permitted. Make a separate folder for building:\nmkdir build; cd build; cmake ..\nBefore that, remove the files already created:\nrm -rf CMakeCache.txt CMakeFiles")
endif (CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)

# Include path for additional CMake library finding scripts
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

# load gunship
find_package (GUNSHIP REQUIRED)

# add gunship as external project
add_subdirectory (${GUNSHIP_ROOT_DIR} ${CMAKE_BINARY_DIR}/Gunship)

get_directory_property (GUNSHIP_LIBS
						DIRECTORY ${GUNSHIP_ROOT_DIR}
						DEFINITION LIBS)
message("gunship libs: " ${GUNSHIP_LIBS})

# The project's include directories
file(GLOB PROJECT_INCLUDES
	${PROJECT_INCLUDES}
	include
	${GUNSHIP_ROOT_DIR}/include)
include_directories(${PROJECT_INCLUDES})

# The project's sources
file(GLOB PROJECT_SOURCES
	source/*.cpp
	include/*.h)

# configure executable
add_executable (${PROJECT_NAME} ${PROJECT_SOURCES})
if (MSVC)
	target_link_libraries (${PROJECT_NAME}
		${CMAKE_BINARY_DIR}/Gunship/Debug/gunship.lib
		${GUNSHIP_LIBS})
else ()
# no libraries to link yet
endif()