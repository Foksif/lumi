#pragma once
#include <string>

namespace lumi {

class MimeResolver {
public:
  static std::string resolve(std::string_view path);
};
} // namespace lumi
