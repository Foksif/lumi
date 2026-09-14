cmake_minimum_required(VERSION 3.20)

project(
    LumiExample
    LANGUAGES CXX
)

add_subdirectory(
    ../..
    ${CMAKE_CURRENT_BINARY_DIR}/lumi
)

add_executable(
    lumi-example
    main.cpp
)

target_link_libraries(
    lumi-example
    PRIVATE
        lumi.app
)

