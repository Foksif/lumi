#pragma once

#include <string>
namespace lumi {

class App {
public:
  App();

  void setFrontend(const std::string &path);

  void run();

private:
  std::string frontendPath;
};

} // namespace lumi
