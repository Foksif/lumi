#pragma once

#include <lumi/resources/Resource.hpp>

#include <string_view>

namespace lumi {

class ResourceManager {
public:
  explicit ResourceManager(Resources resources);

  const Resource *find(std::string_view path) const;

private:
  Resources resources;
};

} // namespace lumi
