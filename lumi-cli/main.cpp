#include <cctype>
#include <filesystem>
#include <fstream>
#include <gio/gio.h>
#include <glib.h>
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

std::string get_mime_type(const std::string &filename) {
  gchar *content_type =
      g_content_type_guess(filename.c_str(), nullptr, 0, nullptr);

  gchar *mime_type = g_content_type_get_mime_type(content_type);

  std::string result = mime_type ? mime_type : "application/octet-stream";

  g_free(content_type);
  g_free(mime_type);

  if (result.rfind("text/", 0) == 0 || result == "application/json" ||
      result == "image/svg+xml") {
    result += "; charset=utf-8";
  }

  return result;
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

  if (!out) {
    std::cerr << "Failed to create resources.hpp\n";
    return 1;
  }

  out << R"(#pragma once

#include <lumi/resources/Resource.hpp>

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

    out << "inline const unsigned char " << variable << "[] = {\n";
    out << "#embed \"" << relative << "\"\n";
    out << "};\n\n";

    resources.push_back({relative, variable});
  }

  out << "inline const Resource files[] = {\n";

  for (const auto &resource : resources) {
    out << "    { \"" << resource.path << "\", \""
        << get_mime_type(resource.path) << "\", " << resource.variable
        << ", sizeof(" << resource.variable << ") },\n";
  }

  out << R"(};

inline const Resources resources{
    files,
    sizeof(files) / sizeof(Resource)
};

} // namespace lumi::generated
)";

  std::cout << "Generated " << resources.size() << " resources.\n";

  return 0;
}
