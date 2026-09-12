#pragma once

#include <string_view>

#include <lumi/Resources.hpp>

namespace lumi {

class ResourceManager {
public:
  explicit ResourceManager(Resources resources);

  const Resource *find(std::string_view path) const;

private:
  Resources resources;
};

} // namespace lumi
