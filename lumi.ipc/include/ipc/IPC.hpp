#pragma once

#include <cstddef>
#include <functional>
#include <string>
#include <string_view>

#include <lumi/webview/WebView.hpp>

namespace lumi {

class IPC {
public:
  using Handler = std::function<void(std::string_view message)>;

  explicit IPC(WebView &webView);

  void emit(std::string_view event, std::string_view message);

  void on(std::string_view event, Handler handler);

private:
  WebView &webView;
};

} // namespace lumi
