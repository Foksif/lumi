#include <filesystem>

#include <iostream>
#include <lumi/App.hpp>
#include <string>
#include <webview/webview.h>

#include <lumi/LocalServer.hpp>
#include <lumi/ResourceManager.hpp>

namespace lumi {

App::App() {}

void App::setFrontend(const std::string &path) { frontendPath = path; }

void App::setTitle(const std::string &setTitle) { title = setTitle; }

void App::setSize(int w, int h) {
  width = w;
  height = h;
}

void App::setResizable(bool value) { resizable = value; }

void App::setFullScreen(bool value) { fullscreen = value; }

void App::setResources(Resources value) {
  resources = value;
  hasResources = true;
}

void App::run() {

  webview::webview window(true, nullptr);

  window.set_title(title);
  window.set_size(width, height, WEBVIEW_HINT_NONE);

  if (hasResources) {
    ResourceManager manager(resources);

    LocalServer server(manager);
    server.start();

    std::string domain =
        "http://127.0.0.1:" + std::to_string(server.getServerPort());
    std::cout << "ServerDomain:" << "\t" << domain << "\n";
    window.navigate(domain);
    window.run();

    server.stop();
  } else {
    auto index = std::filesystem::absolute(frontendPath + "/index.html");

    window.navigate("file://" + index.string());
    window.run();
  }
}
} // namespace lumi
