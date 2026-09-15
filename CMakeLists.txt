cmake_minimum_required(VERSION 3.20)

project(
    Lumi
    VERSION 0.1.0
    DESCRIPTION "Lightweight desktop framework for C++"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(GNUInstallDirs)

include(cmake/Dependencies.cmake)

option(LUMI_BUILD_APP "Build Lumi App module" ON)
option(LUMI_BUILD_WEBVIEW "Build Lumi WebView module" ON)
option(LUMI_BUILD_RESOURCES "Build Lumi Resources module" ON)
option(LUMI_BUILD_EXAMPLES "Build Lumi examples" OFF)
option(LUMI_BUILD_IPC "Build Lumi IPC module" ON)

add_subdirectory(lumi.core)

if(LUMI_BUILD_RESOURCES)
    add_subdirectory(lumi.resources)
endif()

if(LUMI_BUILD_WEBVIEW)
    add_subdirectory(lumi.webview)
endif()

if(LUMI_BUILD_IPC)
    add_subdirectory(lumi.ipc)
endif()

if(LUMI_BUILD_APP)
    add_subdirectory(lumi.app)
endif()

add_library(lumi INTERFACE)

add_library(Lumi::lumi ALIAS lumi)

if(LUMI_BUILD_APP)
    target_link_libraries(
        lumi
        INTERFACE
            lumi.app
    )
endif()

if(LUMI_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
