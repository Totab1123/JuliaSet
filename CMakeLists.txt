cmake_minimum_required(VERSION 3.1)

project(juliaset_sfml CXX)

find_package(SFML 2 REQUIRED graphics window system)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

add_executable(${CMAKE_PROJECT_NAME}
    juliaset_sfml.cpp
)

target_compile_options(${CMAKE_PROJECT_NAME}
    PRIVATE -Ofast -Wall
)

target_link_libraries(${CMAKE_PROJECT_NAME} sfml-graphics sfml-system sfml-window pthread)

set_property(TARGET ${CMAKE_PROJECT_NAME}
    PROPERTY CXX_STANDARD 20
)
