set(CMAKE_NO_SYSTEM_FROM_IMPORTED ON)
set(PROJECT_NAME sample)
set(FLAGS "-g3 -Ofast -std=c++11")
#set(FLAGS "-Wall -Wextra -g3 -Ofast -std=c++11")
project(${PROJECT_NAME})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FLAGS}")

include_directories("../../robin/robin-core/")

file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})
