cmake_minimum_required(VERSION 3.9)
project(robin-bird VERSION 1.0.0 DESCRIPTION "iMX - Artificial Intelligence Framework")

# Compile all the examples
add_subdirectory(examples)

# Find source files
#file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/robin/robin-core/*.cpp")
#file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/robin/robin-nn/*.cpp")

# Include header files
#include_directories(include)

# Create shared library
#add_library(${PROJECT_NAME} SHARED ${SOURCES})

# Install library
#install(TARGETS ${PROJECT_NAME} DESTINATION lib/${PROJECT_NAME})

# Install library headers
#file(GLOB HEADERS "${PROJECT_SOURCE_DIR}/robin/robin-nn/*.h")
#file(GLOB HEADERS "${PROJECT_SOURCE_DIR}/robin/robin-nn/*.h")

#install(FILES ${HEADERS} DESTINATION include/${PROJECT_NAME})




#set (CMAKE_NO_SYSTEM_FROM_IMPORTED ON)
#set(PROJECT_NAME experience)
#project(${PROJECT_NAME})

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g3 -Ofast -std=c++11")

#include_directories("robin/robin-core/")

#file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/robin/robin-core/*.cpp")
#file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/robin/robin-nn/*.cpp")



#add_executable(${PROJECT_NAME} ${SOURCES})

