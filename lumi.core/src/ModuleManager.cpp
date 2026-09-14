#include <lumi/core/ModuleManager.hpp>

namespace lumi {

ModuleManager::~ModuleManager() { shutdown(); }

void ModuleManager::add(std::unique_ptr<Module> module) {
  modules.push_back(std::move(module));
}

void ModuleManager::initialize() {
  if (initialized) {
    return;
  }

  for (auto &module : modules) {
    module->initialize();
  }

  initialized = true;
}

void ModuleManager::shutdown() {
  if (!initialized) {
    return;
  }

  for (auto it = modules.rbegin(); it != modules.rend(); ++it) {
    (*it)->shutdown();
  }

  initialized = false;
}

} // namespace lumi
