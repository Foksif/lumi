#include "frontend/dist/resources.hpp"
#include <lumi/App.hpp>

int main() {
  lumi::App app;

  app.setResources(lumi::generated::resources);
  app.run();

  return 0;
}
