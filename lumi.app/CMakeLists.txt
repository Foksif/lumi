add_library(
    lumi.app
    STATIC
        src/App.cpp
)

target_include_directories(
    lumi.app
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(
    lumi.app
    PUBLIC
        lumi.core
        lumi.resources
        lumi.webview
)
