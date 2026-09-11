cmake_minimum_required(VERSION 3.20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(
    Lumi
    VERSION 0.1.0
    DESCRIPTION "Lightweight desktop framework for C++"
    LANGUAGES CXX
)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    message(STATUS "Using Clang")
elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    message(STATUS "Using GCC")
endif()

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include(GNUInstallDirs)

include(cmake/Dependencies.cmake)


file(GLOB_RECURSE LUMI_SOURCES
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)


add_compile_definitions(WEBVIEW_GTK=1)
add_library(lumi STATIC
    ${LUMI_SOURCES}
)


add_library(Lumi::lumi ALIAS lumi)


target_link_libraries(lumi
    PUBLIC
        webview::core
    PRIVATE
        nlohmann_json::nlohmann_json
        httplib::httplib
)


target_include_directories(lumi
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)



# Установка библиотеки

install(
    TARGETS lumi
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)


install(
    DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
