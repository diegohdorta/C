cmake_minimum_required(VERSION 3.5)

set (CMAKE_NO_SYSTEM_FROM_IMPORTED ON)
set(PROJECT_NAME experience)
project(${PROJECT_NAME})

find_package(OpenCV REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(Threads REQUIRED)
pkg_check_modules(GTKMM gtkmm-3.0)

link_directories(${GTKMM_LIBRARY_DIRS})

include_directories(${GTKMM_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -fsanitize=leak -fno-omit-frame-pointer -g3 -Ofast -std=c++11")

include_directories(include)

file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})

target_link_libraries(${PROJECT_NAME} ${GTKMM_LIBRARIES})

target_link_libraries(${PROJECT_NAME}  ${CMAKE_THREAD_LIBS_INIT})

