cmake_minimum_required(VERSION 3.22.1)

project(top_down_shooter)

file(GLOB_RECURSE SOURCES src/*.cpp include/*.h)
file(GLOB_RECURSE RESOURCES_FONTS resources/fonts/*)
file(GLOB_RECURSE RESOURCES_TEXTURES resources/textures/*)
file(GLOB_RECURSE RESOURCES_MUSIC resources/music/*)
file(GLOB_RECURSE RESOURCES_SOUNDS resources/sounds/*)

set(SFML_STATIC_LIBRARIES TRUE)

#Define path to your SFML root here (for example, C:/libs/SFML-2.6.1)
set(SFML_ROOT "/home/kndnb/Downloads/SFML-2.6.1-linux-gcc-64-bit/SFML-2.6.1")
#set(SFML_ROOT "path/to/your/SFML/root/folder")

set(SFML_DIR "${SFML_ROOT}/lib/cmake/SFML")
set(EXECUTABLE_NAME "top_down_shooter")
add_executable(${EXECUTABLE_NAME} ${SOURCES} ${RESOURCES_FONTS} ${RESOURCES_TEXTURES} ${RESOURCES_MUSIC} ${RESOURCES_SOUNDS})

target_compile_options(${EXECUTABLE_NAME} PUBLIC -std=c++14 -Wall -g -O3)

file(COPY ${RESOURCES_FONTS} DESTINATION resources/fonts)
file(COPY ${RESOURCES_TEXTURES} DESTINATION resources/textures)
file(COPY ${RESOURCES_MUSIC} DESTINATION resources/music)
file(COPY ${RESOURCES_SOUNDS} DESTINATION resources/sounds)

include_directories(${PROJECT_SOURCE_DIR}/include)

find_package(SFML 2.6.1 REQUIRED network audio graphics window system)
if(SFML_FOUND)
  target_link_libraries(${EXECUTABLE_NAME} sfml-graphics sfml-audio sfml-window sfml-system)
endif()

