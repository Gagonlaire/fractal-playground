cmake_minimum_required(VERSION 3.14)
project(fractal-playground)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_CURRENT_BINARY_DIR ${CMAKE_BINARY_DIR})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-O3)

if (APPLE)
    set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
endif ()

set(SOURCE_FILES
        src/main.cpp
        src/utils.cpp
        src/UI/UI.cpp
        src/UI/MaterialButton.cpp
        src/UI/ViewBuilder.cpp
        src/UI/MaterialSelector.cpp
        src/functions/mandlebrot.cpp
        src/functions/mandlebar.cpp
        src/functions/burning_ships.cpp
        src/functions/julia.cpp)
add_executable(fractal-playground ${SOURCE_FILES})

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS} includes)
target_link_libraries(fractal-playground sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
