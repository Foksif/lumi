cmake_minimum_required(VERSION 3.20)

project(lumi.ipc LANGUAGES CXX)

add_library(
  lumi.ipc
  STATIC
  src/IPC.cpp
)

add_library(Lumi::IPC ALIAS lumi.ipc)

target_include_directories(
  lumi.ipc
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(
  lumi.ipc
  PUBLIC
  Lumi::WebView
)

target_compile_features(
  lumi.ipc
  PUBLIC
  cxx_std_20
)
