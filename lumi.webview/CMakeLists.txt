cmake_minimum_required(VERSION 3.20)

project(lumi.webview LANGUAGES CXX)

find_package(PkgConfig REQUIRED)

pkg_check_modules(GTK4 REQUIRED IMPORTED_TARGET gtk4)
pkg_check_modules(WEBKITGTK REQUIRED IMPORTED_TARGET webkitgtk-6.0)

add_library(
lumi.webview
STATIC
src/WebView.cpp
src/WebViewModule.cpp
src/platform/linux/LinuxWebView.cpp
src/platform/linux/LinuxWebViewModule.cpp
)

add_library(Lumi::WebView ALIAS lumi.webview)

target_include_directories(
lumi.webview
PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_include_directories(
lumi.webview
PRIVATE
${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(
lumi.webview
PUBLIC
Lumi::Core
Lumi::Resources
PRIVATE
PkgConfig::GTK4
PkgConfig::WEBKITGTK
)

target_compile_features(
lumi.webview
PUBLIC
cxx_std_20
)

