#pragma once

#include <cstddef>
namespace lumi {

struct Resource {
  const char *path;
  const char *content_type;
  const unsigned char *data;
  std::size_t data_size;
};

struct Resources {
  const Resource *files;
  std::size_t count;
};

} // namespace lumi
