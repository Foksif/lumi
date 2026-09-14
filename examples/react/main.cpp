#include "frontend/dist/resources.hpp"

#include <lumi/app/App.hpp>

int main() {
  lumi::App app;

  auto &webview = app.webView();

  webview.setResources(lumi::generated::resources);
  webview.setTitle("Lumi React");
  webview.setSize(1280, 720);

  app.run();

  return 0;
}
