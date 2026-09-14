#include <lumi/resources/ResourceManager.hpp>

namespace lumi {

ResourceManager::ResourceManager(Resources resources) : resources(resources) {}

const Resource *ResourceManager::find(std::string_view path) const {
  for (std::size_t i = 0; i < resources.count; ++i) {
    const auto &resource = resources.files[i];

    if (path == resource.path) {
      return &resource;
    }
  }

  return nullptr;
}

} // namespace lumi
