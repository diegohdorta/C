set(CMAKE_NO_SYSTEM_FROM_IMPORTED ON)
set(PROJECT_NAME handwritten-digit-file)
set(FLAGS "-g3 -Ofast -std=c++11")
#set(FLAGS "-Wall -Wextra -g3 -Ofast -std=c++11")
project(${PROJECT_NAME})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FLAGS}")

include (FindPkgConfig)
if (NOT PKG_CONFIG_FOUND)
    message (FATAL_ERROR "pkg-config not found")
endif ()

# check for libpng
pkg_check_modules (LIBPNG libpng16 REQUIRED)
if (NOT LIBPNG_FOUND)
    message(FATAL_ERROR "You don't seem to have libpng16 development libraries installed")
else ()
    include_directories (${LIBPNG_INCLUDE_DIRS})
    link_directories (${LIBPNG_LIBRARY_DIRS})
    link_libraries (${LIBPNG_LIBRARIES})
endif ()

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/media
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# I need to copy the params file from the handwritten-digit folder

include_directories("../../robin/robin-core/")
include_directories("../../robin/robin-nn/")

file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/*.cpp" ../../robin/robin-nn/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES} ${LIBPNG_LINK_FLAGS})
