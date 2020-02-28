set(CMAKE_NO_SYSTEM_FROM_IMPORTED ON)
set(PROJECT_NAME handwritten-digit)
set(FLAGS "-g3 -Ofast -std=c++11")
#set(FLAGS "-Wall -Wextra -g3 -Ofast -std=c++11")
project(${PROJECT_NAME})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FLAGS}")

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/mnist-training.rb
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/mnist-test.rb
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

include_directories("../../robin/robin-core/")
include_directories("../../robin/robin-nn/")

file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/*.cpp" ../../robin/robin-nn/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})
