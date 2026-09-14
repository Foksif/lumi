add_library(lumi.resources STATIC
    src/ResourceManager.cpp
)

add_library(Lumi::Resources ALIAS lumi.resources)

target_link_libraries(lumi.resources
    PUBLIC
        Lumi::Core
)

target_include_directories(lumi.resources
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
