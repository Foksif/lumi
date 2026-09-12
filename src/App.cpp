#undef CPPHTTPLIB_ZLIB_SUPPORT

#include <filesystem>

#include <iostream>
#include <lumi/App.hpp>
#include <string>
#include <webview/webview.h>

#include <lumi/ResourceManager.hpp>

namespace lumi {

App::App() {}

void App::setFrontend(const std::string &path) { frontendPath = path; }

void App::setTitle(const std::string &setTitle) { title = setTitle; }

void App::setSize(int w, int h) {
  width = w;
  height = h;
}

void App::setResizable(bool value) { resizable = value; }

void App::setFullScreen(bool value) { fullscreen = value; }

void App::setResources(Resources value) {
  resources = value;
  hasResources = true;
}

ResourceManager *manager;
static void on_gtk_uri_scheme_request(WebKitURISchemeRequest *request,
                                      gpointer user_data) {
  const gchar *path = webkit_uri_scheme_request_get_uri(request);
  std::cout << "[on_gtk_uri_scheme_request] Браузер запросил путь: " << path
            << std::endl;

  std::string req_path = path;
  if (req_path.rfind("app://", 0) == 0) {
    req_path = req_path.substr(6);
  }
  if (!req_path.empty() && req_path[0] == '/') {
    req_path = req_path.substr(1);
  }
  auto cut_pos = req_path.find_first_of("#?");
  if (cut_pos != std::string_view::npos) {
    req_path = req_path.substr(0, cut_pos);
  }

  auto resource = manager->find(req_path);
  if (resource == nullptr) {
    auto spaFall = std::string_view(path).find_last_of('.');
    if (spaFall == std::string_view::npos) {
      resource = manager->find("index.html");

      if (resource != nullptr) {
        goto end;
      }
    }
    std::cout << "[on_gtk_uri_scheme_request] - Ответ: 404 Not Found"
              << std::endl;
    GError *error = g_error_new(WEBKIT_NETWORK_ERROR,
                                WEBKIT_NETWORK_ERROR_FILE_DOES_NOT_EXIST,
                                "Resource '%s' not found", req_path.c_str());

    webkit_uri_scheme_request_finish_error(request, error);
    g_error_free(error);
    return;
  }

end:
  std::cout << "[on_gtk_uri_scheme_request] - Ответ: " << resource->data_size
            << " байт, по адресу: " << resource->path << ", "
            << resource->content_type << std::endl;
  GInputStream *stream = g_memory_input_stream_new_from_data(
      resource->data, resource->data_size, NULL);
  webkit_uri_scheme_request_finish(request, stream, resource->data_size,
                                   resource->content_type);
  g_object_unref(stream);
}

void App::run() {
  webview::webview window(true, nullptr);

  window.set_title(title);

  if (hasResources) {
    manager = new ResourceManager(resources);

    WebKitWebView *web_view =
        WEBKIT_WEB_VIEW(window.browser_controller().value());
    WebKitWebContext *context = webkit_web_view_get_context(web_view);

    webkit_web_context_register_uri_scheme(
        context, "app", on_gtk_uri_scheme_request, NULL, NULL);

    window.navigate("app://");
    window.run();

    delete manager;
  } else {
    auto index = std::filesystem::absolute(frontendPath + "/index.html");

    window.navigate("file://" + index.string());
    window.run();
  }
}
} // namespace lumi
