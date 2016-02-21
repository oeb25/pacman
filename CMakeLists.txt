cmake_minimum_required(VERSION 3.4)
project (PacMan)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PacMan_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIR})

file(GLOB SOURCES "src/*.cpp")

add_executable(app ${SOURCES})
target_link_libraries(app ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY})