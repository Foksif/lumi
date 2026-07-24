cmake_minimum_required(VERSION 3.20)

project(
    Lumi
    VERSION 0.1.0
    DESCRIPTION "Lightweight desktop framework for C++"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE LUMI_SOURCES
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_library(lumi STATIC ${LUMI_SOURCES})

target_include_directories(lumi
    PUBLIC
        "${PROJECT_SOURCE_DIR}/include"
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(test-app
    test/main.cpp
)

target_link_libraries(test-app
    PRIVATE
        lumi
)
