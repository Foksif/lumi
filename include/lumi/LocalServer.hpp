#include <cstdint>
#include <lumi/ResourceManager.hpp>
#include <memory>

namespace lumi {
class LocalServer {
public:
  explicit LocalServer(ResourceManager &resources);

  void start();
  void stop();

  uint16_t getServerPort();

  ~LocalServer();

private:
  uint16_t serverPort;
  ResourceManager &resources;

  class Impl;
  std::unique_ptr<Impl> impl;
};
} // namespace lumi
