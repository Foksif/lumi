add_library(lumi.core STATIC
    src/Module.cpp
    src/ModuleManager.cpp
)

add_library(Lumi::Core ALIAS lumi.core)

target_include_directories(lumi.core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
