#include <lumi/ResourceManager.hpp>

namespace lumi {

ResourceManager::ResourceManager(Resources r) : resources(r) {}

const Resource *ResourceManager::find(std::string_view path) const {
  for (size_t i = 0; i < resources.count; ++i) {
    const auto &file = resources.files[i];

    if (path == file.path)
      return &file;
  }

  return nullptr;
}

} // namespace lumi
