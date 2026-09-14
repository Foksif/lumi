#include <lumi/webview/WebView.hpp>

#include "platform/linux/LinuxWebView.hpp"

namespace lumi {

class WebView::Impl {
public:
  LinuxWebView platform;
};

WebView::WebView() : impl(std::make_unique<Impl>()) {}

WebView::~WebView() = default;

WebView::WebView(WebView &&other) noexcept = default;

WebView &WebView::operator=(WebView &&other) noexcept = default;

void WebView::setTitle(const std::string &title) {
  impl->platform.setTitle(title);
}

void WebView::setSize(int width, int height) {
  impl->platform.setSize(width, height);
}

void WebView::setResizable(bool value) { impl->platform.setResizable(value); }

void WebView::setFullscreen(bool value) { impl->platform.setFullscreen(value); }

void WebView::navigate(const std::string &url) { impl->platform.navigate(url); }

void WebView::setFrontend(const std::string &path) {
  impl->platform.setFrontend(path);
}

void WebView::setResources(Resources resources) {
  impl->platform.setResources(resources);
}

void WebView::run() { impl->platform.run(); }

} // namespace lumi
