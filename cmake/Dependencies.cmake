include(FetchContent)

FetchContent_Declare(
    webview
    GIT_REPOSITORY https://github.com/webview/webview
)

FetchContent_MakeAvailable(webview)

find_package(nlohmann_json REQUIRED)
