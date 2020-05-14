cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(SnakeGame_GG)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2TTF REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} src)
include_directories(${SDL2_IMAGE_DIRS})
include_directories(${SDL2_MIXER_DIRS})
include_directories(${SDL2TTF_DIRS})

add_executable(${PROJECT_NAME} src/main.cpp src/game.cpp src/controller.cpp
 src/renderer.cpp src/snake.cpp src/soundplayer.cpp src/texture.cpp)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES}
 ${SDL2_MIXER_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2TTF_LIBRARY}) 