cmake_minimum_required(VERSION 3.0)

project(top_down_shooter)

file(GLOB_RECURSE SOURCES src/*.cpp include/*.h)
file(GLOB_RECURSE RESOURCES_FONTS resources/fonts/*)
file(GLOB_RECURSE RESOURCES_TEXTURES resources/textures/*)
file(GLOB_RECURSE RESOURCES_MUSIC resources/music/*)
file(GLOB_RECURSE RESOURCES_SOUNDS resources/sounds/*)

set(EXECUTABLE_NAME "top_down_shooter")
add_executable(${EXECUTABLE_NAME} ${SOURCES} ${RESOURCES_FONTS} ${RESOURCES_TEXTURES} ${RESOURCES_MUSIC} ${RESOURCES_SOUNDS})

target_compile_options(${EXECUTABLE_NAME} PUBLIC -std=c++11 -Wall -g -O3)

file(COPY ${RESOURCES_FONTS} DESTINATION resources/fonts)
file(COPY ${RESOURCES_TEXTURES} DESTINATION resources/textures)
file(COPY ${RESOURCES_MUSIC} DESTINATION resources/music)
file(COPY ${RESOURCES_SOUNDS} DESTINATION resources/sounds)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

find_package(SFML 2.3.2 REQUIRED network audio graphics window system)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

