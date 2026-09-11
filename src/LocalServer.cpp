#include <chrono>
#include <lumi/LocalServer.hpp>
#include <memory>
#include <random>
#include <stdexcept>

#include <arpa/inet.h>
#include <httplib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <thread>
#include <unistd.h>

#include <lumi/MimeResolver.hpp>

namespace lumi {
class LocalServer::Impl {
public:
  std::thread serverThread;
  httplib::Server server;
};

static int find_free_port();

LocalServer::LocalServer(ResourceManager &resources)
    : resources(resources), serverPort(find_free_port()),
      impl(std::make_unique<Impl>()) {}

LocalServer::~LocalServer() { stop(); }

void LocalServer::start() {
  impl->server.Get(
      R"(.*)", [&](const httplib::Request &req, httplib::Response &res) {
        std::cerr << "\n[LocalServer] request\n";
        std::cerr << "  thread: " << std::this_thread::get_id() << '\n';
        std::cerr << "  method: " << req.method << '\n';
        std::cerr << "  path:   " << req.path << '\n';

        std::string path = req.path;

        if (path == "/")
          path = "/index.html";

        if (!path.empty() && path.front() == '/')
          path.erase(0, 1);

        std::cerr << "  lookup: " << path << '\n';

        auto resource = resources.find(path);

        if (!resource) {
          std::cerr << "  result: NOT FOUND\n";

          auto spaFall = path.find_last_of('.');
          if (spaFall == std::string_view::npos) {
            std::cerr << "  SPA fallback -> index.html\n";

            path = "index.html";
            resource = resources.find(path);

            if (!resource) {
              std::cerr << "  fallback result: NOT FOUND\n";
              res.status = 404;
              res.set_content("404 Not Found", "text/plain");
              return;
            }
          } else {
            res.status = 404;
            res.set_content("404 Not Found", "text/plain");
            return;
          }
        }

        auto mime = MimeResolver::resolve(path);

        std::cerr << "  result: FOUND\n";
        std::cerr << "  size:   " << resource->size << '\n';
        std::cerr << "  mime:   " << mime << '\n';

        res.set_content(reinterpret_cast<const char *>(resource->data),
                        resource->size, mime);
      });
  impl->serverThread =
      std::thread([&]() { impl->server.listen("127.0.0.1", serverPort); });
}

void LocalServer::stop() {
  impl->server.stop();

  if (impl->serverThread.joinable()) {
    impl->serverThread.join();
  }
}

uint16_t LocalServer::getServerPort() { return serverPort; }

static bool is_port_free(int port) {
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0)
    return false;

  sockaddr_in addr{};
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  addr.sin_port = htons(port);

  int opt = 1;
#ifdef _WIN32
  setsockopt(sock, SOL_SOCKET, SO_REUSEADDR,
             reinterpret_cast<const char *>(&opt), sizeof(opt));
#else
  setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
#endif

  int result = bind(sock, reinterpret_cast<sockaddr *>(&addr), sizeof(addr));

#ifdef _WIN32
  closesocket(sock);
#else
  close(sock);
#endif

  return (result == 0);
}

static int find_free_port() {
  std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
  std::uniform_int_distribution<int> dist(49152, 65535);

  for (int i = 0; i < 100; ++i) {
    int port = dist(rng);
    if (is_port_free(port)) {
      return port;
    }
  }
  throw std::runtime_error("Cannot find free port");
}
} // namespace lumi
