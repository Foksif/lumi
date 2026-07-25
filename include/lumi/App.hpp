#pragma once

#include "lumi/Resources.hpp"
#include <string>

namespace lumi {

class App {
public:
  App();

  void setFrontend(const std::string &path);
  void setResources(Resources resources);

  void setTitle(const std::string &setTitle);
  void setSize(int width, int height);

  void setResizable(bool value);
  void setFullScreen(bool value);

  void run();

private:
  std::string frontendPath;

  std::string title = "Lumi App";
  int width = 800;
  int height = 600;

  bool resizable = true;
  bool fullscreen = false;

  Resources resources{};
  bool hasResources = false;
};

} // namespace lumi
