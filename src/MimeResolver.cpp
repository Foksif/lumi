#include <lumi/MimeResolver.hpp>
#include <vector>

namespace lumi {

std::string MimeResolver::resolve(std::string_view path) {
  auto position = path.find_last_of('.');
  if (position == std::string_view::npos) {
    return "application/octet-stream";
  }

  size_t pathSize = path.size();
  size_t extendSize = pathSize - position;

  if (extendSize == 1) {
    return "application/octet-stream";
  }
  std::vector<char> exten;

  for (size_t i = 0; i < extendSize; i++) {
    exten.push_back(path[position + i]);
  }

  std::string pathExten(exten.data(), exten.size());

  if (pathExten == ".html" || pathExten == ".htm") {
    return "text/html";
  } else if (pathExten == ".css") {
    return "text/css";
  } else if (pathExten == ".js" || pathExten == ".mjs") {
    return "text/javascript";
  } else if (pathExten == ".json") {
    return "application/json";
  } else if (pathExten == ".xml") {
    return "application/xml";
  } else if (pathExten == ".txt") {
    return "text/plain";
  } else if (pathExten == ".png") {
    return "image/png";
  } else if (pathExten == ".jpg" || pathExten == ".jpeg") {
    return "image/jpeg";
  } else if (pathExten == ".gif") {
    return "image/gif";
  } else if (pathExten == ".webp") {
    return "image/webp";
  } else if (pathExten == ".svg") {
    return "image/svg+xml";
  } else if (pathExten == ".ico") {
    return "image/x-icon";
  } else if (pathExten == ".avif") {
    return "image/avif";
  } else if (pathExten == ".woff") {
    return "font/woff";
  } else if (pathExten == ".woff2") {
    return "font/woff2";
  } else if (pathExten == ".ttf") {
    return "font/ttf";
  } else if (pathExten == ".otf") {
    return "font/otf";
  } else if (pathExten == ".wasm") {
    return "application/wasm";
  } else if (pathExten == ".webmanifest") {
    return "application/manifest+json";
  }

  return "application/octet-stream";
}
} // namespace lumi
