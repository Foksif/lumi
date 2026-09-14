#pragma once

#include <memory>
#include <string>

#include <lumi/resources/Resource.hpp>

namespace lumi {

class WebView {
public:
  WebView();
  ~WebView();

  WebView(const WebView &) = delete;
  WebView &operator=(const WebView &) = delete;

  WebView(WebView &&) noexcept;
  WebView &operator=(WebView &&) noexcept;

  void setTitle(const std::string &title);
  void setSize(int width, int height);
  void setResizable(bool value);
  void setFullscreen(bool value);

  void navigate(const std::string &url);
  void setFrontend(const std::string &path);

  void setResources(Resources resources);

  void run();

private:
  class Impl;
  std::unique_ptr<Impl> impl;
};

} // namespace lumi
