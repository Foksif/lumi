#pragma once

#include "lumi/webview/WebView.hpp"
#include <string>
namespace lumi {

class IPC {
public:
  explicit IPC(WebView &webView);

  void ipcToJs(const std::string &message);
  void ipcFromJs(void (*callback)(const char *, size_t));

private:
  WebView &webView;
};
} // namespace lumi
