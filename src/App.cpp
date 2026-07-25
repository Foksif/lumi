#include <filesystem>
#include <httplib.h>
#include <iostream>

#include <lumi/App.hpp>
#include <string>
#include <thread>
#include <webview/webview.h>

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

    httplib::Server server;

    server.Get(R"(.*)",
               [&](const httplib::Request &req, httplib::Response &res) {
                 std::string path = req.path;

                 if (path == "/")
                   path = "/index.html";

                 if (!path.empty() && path.front() == '/')
                   path.erase(0, 1);

                 auto resource = manager.find(path);

                 if (!resource) {
                   res.status = 404;
                   res.set_content("404 Not Found", "text/plain");
                   return;
                 }

                 res.set_content(reinterpret_cast<const char *>(resource->data),
                                 resource->size, "text/html");
               });

    std::thread serverThread([&]() { server.listen("127.0.0.1", 38451); });

    window.navigate("http://127.0.0.1:38451/");
    window.run();

    server.stop();
    serverThread.join();
  } else {
    auto index = std::filesystem::absolute(frontendPath + "/index.html");

    window.navigate("file://" + index.string());
    window.run();
  }
}
} // namespace lumi
