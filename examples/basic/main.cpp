#include <lumi/App.hpp>

int main() {
  lumi::App app;

  app.setFrontend("frontend");

  app.run();

  return 0;
}
