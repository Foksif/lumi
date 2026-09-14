#pragma once

#include <lumi/webview/WebView.hpp>

namespace lumi {

class App {
public:
  App();
  ~App();

  App(const App &) = delete;
  App &operator=(const App &) = delete;

  WebView &webView();

  void run();

private:
  WebView view;
};

} // namespace lumi
