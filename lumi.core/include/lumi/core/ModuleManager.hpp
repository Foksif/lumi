#pragma once

#include <lumi/core/Module.hpp>

#include <memory>
#include <vector>

namespace lumi {

class ModuleManager {
public:
  ModuleManager() = default;
  ~ModuleManager();

  ModuleManager(const ModuleManager &) = delete;
  ModuleManager &operator=(const ModuleManager &) = delete;

  void add(std::unique_ptr<Module> module);

  void initialize();
  void shutdown();

private:
  std::vector<std::unique_ptr<Module>> modules;
  bool initialized = false;
};

} // namespace lumi
