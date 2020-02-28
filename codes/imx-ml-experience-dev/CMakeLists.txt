cmake_minimum_required(VERSION 3.5)

# Set the name and the supported language of the project
set(PROJECT_NAME imx-ml-experience)
project(${PROJECT_NAME})

# Use the package PkgConfig to detect GTK+ headers/library files
FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTK3 REQUIRED gtk+-3.0)

# Setup CMake to use GTK+, tell the compiler where to look for headers
# and to the linker where to look for libraries

include_directories(include)

INCLUDE_DIRECTORIES(${GTK3_INCLUDE_DIRS})
LINK_DIRECTORIES(${GTK3_LIBRARY_DIRS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -rdynamic -Wl,--export-dynamic")
# Add other flags to the compiler
ADD_DEFINITIONS(${GTK3_CFLAGS_OTHER})

file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.c")
add_executable(${PROJECT_NAME} ${SOURCES})


option(OP_IMX_ML_DEBUG "Enable debugging mode" 1)

if(OP_IMX_ML_DEBUG)
  add_definitions(-DIMX_ML_DEBUG)
endif()

# Link the target to the GTK+ libraries
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${GTK3_LIBRARIES})
