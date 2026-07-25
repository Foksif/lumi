#pragma once

#include <cstddef>
namespace lumi {

struct Resource {
  const char *path;
  const unsigned char *data;
  std::size_t size;
};

struct Resources {
  const Resource *files;
  std::size_t count;
};

} // namespace lumi
