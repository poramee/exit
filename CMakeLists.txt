cmake_minimum_required(VERSION 3.11)
project(Exit)

set(dir "${CMAKE_CURRENT_SOURCE_DIR}")
set(SOURCES Additional/Setup.cpp Additional/Movement.cpp Additional/Map.cpp Additional Additional/Level.cpp  Additional/UI.cpp)

include_directories(C:/Users/Poramee/Documents/SFML-2.5.0/include Additional)
link_directories(C:/Users/Poramee/Documents/SFML-2.5.0/lib)

add_library(LibSetup Additional/Setup.hpp Additional/Setup.cpp)
add_library(LibMovement Additional/Setup.hpp Additional/Movement.hpp Additional/Movement.cpp)
add_library(LibMap Additional/Map.hpp Additional/Map.cpp)
add_library(LibLevel Additional/Level.hpp Additional/Level.cpp)
add_library(LibUI Additional/UI.hpp Additional/UI.cpp)

set (CMAKE_CXX_STANDARD 14)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${dir})
set(CMAKE_BUILD_FILES_DIRECTORY ${dir})
set(CMAKE_BUILD_DIRECTORY ${dir})
set(CMAKE_BINARY_DIR  ${dir})
SET(EXECUTABLE_OUTPUT_PATH ${dir})
SET(LIBRARY_OUTPUT_PATH ${dir})
SET(CMAKE_CACHEFILE_DIR ${dir})
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

add_executable (Exit main.cpp ${SOURCES})
set_target_properties(Exit PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Exit LibSetup LibMovement LibMap LibLevel LibUI sfml-main-d.lib sfml-graphics-d.lib sfml-window-d.lib sfml-system-d.lib sfml-audio-d.lib)
