#include <filesystem>
#include <iostream>

#include <lumi/App.hpp>
#include <string>
#include <webview/webview.h>

namespace lumi {

App::App() {}

void App::setFrontend(const std::string &path) { frontendPath = path; }

void App::run() {
  /*
  std::cout << "cwd: " << std::filesystem::current_path() << std::endl;

  std::cout << "frontend: " << std::filesystem::absolute(frontendPath)
            << std::endl;
  */

  webview::webview window(true, nullptr);

  window.set_title("Lumi");
  window.set_size(800, 600, WEBVIEW_HINT_NONE);

  auto index = std::filesystem::absolute(frontendPath + "/index.html");

  // std::cout << "index: " << index << std::endl;

  window.navigate("file://" + index.string());
  window.run();
}
} // namespace lumi
