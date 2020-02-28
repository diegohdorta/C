# Copyright (c) 2019 Diego Dorta <diego.dorta@nxp.com>
# SPDX-License-Identifier:	GPL-3.0+
cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME gtk3-ml-experience)
project(${PROJECT_NAME})

FIND_PACKAGE(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

link_directories(${GTK3_LIBRARY_DIRS})
include_directories(${GTK3_INCLUDE_DIRS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -g -std=c++11")

include_directories(include)
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

option(OP_USE_NAME_GTK "Enable GTK Main Window Name" ON)

if(OP_USE_NAME_GTK)
  add_definitions(-DUSE_NAME_GTK)
endif()

target_link_libraries(${PROJECT_NAME} ${GTK3_LIBRARIES})
