#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

struct ResourceInfo {
  std::string path;
  std::string variable;
};

std::vector<unsigned char> readFile(const fs::path &path) {
  std::ifstream file(path, std::ios::binary);

  return {std::istreambuf_iterator<char>(file),
          std::istreambuf_iterator<char>()};
}

std::string sanitize(std::string str) {
  for (char &c : str) {
    if (!std::isalnum(static_cast<unsigned char>(c)))
      c = '_';
  }

  return str;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cerr << "Usage: generator <directory>\n";
    return 1;
  }

  fs::path root = argv[1];

  if (!fs::exists(root)) {
    std::cerr << "Directory does not exist.\n";
    return 1;
  }

  std::ofstream out(root / "resources.hpp");

  out << R"(#pragma once

#include <lumi/Resources.hpp>

namespace lumi::generated {

)";

  std::vector<ResourceInfo> resources;

  for (const auto &entry : fs::recursive_directory_iterator(root)) {
    if (!entry.is_regular_file())
      continue;

    if (entry.path().filename() == "resources.hpp")
      continue;

    auto relative = fs::relative(entry.path(), root).generic_string();
    auto variable = sanitize(relative);

    out << "inline const unsigned char " << variable << "[] = {\n#embed "
        << fs::relative(entry.path(), root) << "\n};\n\n";

    resources.push_back({relative, variable});
  }

  out << "inline const Resource files[] = {\n";

  for (const auto &r : resources) {
    out << "    { \"" << r.path << "\", " << r.variable << ", sizeof("
        << r.variable << ") },\n";
  }

  out << R"(};

inline const Resources resources{
    files,
    sizeof(files) / sizeof(Resource)
};

} // namespace lumi::generated
)";

  std::cout << "Generated " << resources.size() << " resources.\n";
}
