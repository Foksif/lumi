#include "LinuxWebView.hpp"

#include <filesystem>
#include <memory>
#include <string>

#include <gtk/gtk.h>
#include <webkit/webkit.h>

#include <lumi/resources/ResourceManager.hpp>

#include "LinuxWebViewModule.hpp"

namespace lumi {

class LinuxWebView::Impl {
public:
  GtkWidget *window = nullptr;
  WebKitWebView *webView = nullptr;
  WebKitWebContext *context = nullptr;
  GMainLoop *mainLoop = nullptr;

  std::unique_ptr<ResourceManager> resourceManager;

  std::string title = "Lumi App";
  std::string frontendPath;

  int width = 800;
  int height = 600;

  bool resizable = true;
  bool fullscreen = false;

  Resources resources{};
  bool hasResources = false;

  static void destroyWindow(GtkWidget *widget, gpointer userData) {
    auto *impl = static_cast<Impl *>(userData);

    if (impl->window == widget) {
      impl->window = nullptr;
    }

    if (impl->mainLoop != nullptr && g_main_loop_is_running(impl->mainLoop)) {
      g_main_loop_quit(impl->mainLoop);
    }
  }

  static void finishNotFound(WebKitURISchemeRequest *request,
                             const std::string &path) {
    GError *error = g_error_new(WEBKIT_NETWORK_ERROR,
                                WEBKIT_NETWORK_ERROR_FILE_DOES_NOT_EXIST,
                                "Resource '%s' not found", path.c_str());

    webkit_uri_scheme_request_finish_error(request, error);
    g_error_free(error);
  }

  static void handleUriScheme(WebKitURISchemeRequest *request,
                              gpointer userData) {
    auto *impl = static_cast<Impl *>(userData);

    const gchar *uri = webkit_uri_scheme_request_get_uri(request);

    if (uri == nullptr) {
      finishNotFound(request, "unknown");
      return;
    }

    std::string path = uri;

    if (path.rfind("app://", 0) == 0) {
      path = path.substr(6);
    }

    if (!path.empty() && path.front() == '/') {
      path.erase(0, 1);
    }

    const auto queryPosition = path.find_first_of("?#");

    if (queryPosition != std::string::npos) {
      path.erase(queryPosition);
    }

    if (path.empty()) {
      path = "index.html";
    }

    const Resource *resource = nullptr;

    if (impl->resourceManager) {
      resource = impl->resourceManager->find(path);
    }

    if (resource == nullptr) {
      const bool hasExtension = path.find_last_of('.') != std::string::npos;

      if (!hasExtension && impl->resourceManager) {
        resource = impl->resourceManager->find("index.html");
      }
    }

    if (resource == nullptr) {
      finishNotFound(request, path);
      return;
    }

    GInputStream *stream = G_INPUT_STREAM(g_memory_input_stream_new_from_data(
        resource->data, resource->data_size, nullptr));

    webkit_uri_scheme_request_finish(request, stream, resource->data_size,
                                     resource->content_type);

    g_object_unref(stream);
  }

  void registerScheme() {
    webkit_web_context_register_uri_scheme(context, "app", handleUriScheme,
                                           this, nullptr);
  }

  void createWindow() {
    window = gtk_window_new();

    gtk_window_set_title(GTK_WINDOW(window), title.c_str());

    gtk_window_set_default_size(GTK_WINDOW(window), width, height);

    gtk_window_set_resizable(GTK_WINDOW(window), resizable);

    g_signal_connect(window, "destroy", G_CALLBACK(destroyWindow), this);

    webView = WEBKIT_WEB_VIEW(webkit_web_view_new());

    context = webkit_web_view_get_context(webView);

    gtk_window_set_child(GTK_WINDOW(window), GTK_WIDGET(webView));

    if (fullscreen) {
      gtk_window_fullscreen(GTK_WINDOW(window));
    }

    gtk_window_present(GTK_WINDOW(window));
  }

  void load() {
    if (hasResources) {
      registerScheme();

      webkit_web_view_load_uri(webView, "app:///");

      return;
    }

    if (frontendPath.empty()) {
      return;
    }

    const auto index = std::filesystem::absolute(
        std::filesystem::path(frontendPath) / "index.html");

    const auto uri = std::string("file://") + index.string();

    webkit_web_view_load_uri(webView, uri.c_str());
  }
};

LinuxWebView::LinuxWebView() : impl(std::make_unique<Impl>()) {
  LinuxWebViewModule::initialize();
}

LinuxWebView::~LinuxWebView() {
  if (impl->window != nullptr) {
    gtk_window_destroy(GTK_WINDOW(impl->window));

    impl->window = nullptr;
  }
}

void LinuxWebView::setTitle(const std::string &title) {
  impl->title = title;

  if (impl->window != nullptr) {
    gtk_window_set_title(GTK_WINDOW(impl->window), impl->title.c_str());
  }
}

void LinuxWebView::setSize(int width, int height) {
  impl->width = width;
  impl->height = height;

  if (impl->window != nullptr) {
    gtk_window_set_default_size(GTK_WINDOW(impl->window), width, height);
  }
}

void LinuxWebView::setResizable(bool value) {
  impl->resizable = value;

  if (impl->window != nullptr) {
    gtk_window_set_resizable(GTK_WINDOW(impl->window), value);
  }
}

void LinuxWebView::setFullscreen(bool value) {
  impl->fullscreen = value;

  if (impl->window == nullptr) {
    return;
  }

  if (value) {
    gtk_window_fullscreen(GTK_WINDOW(impl->window));
  } else {
    gtk_window_unfullscreen(GTK_WINDOW(impl->window));
  }
}

void LinuxWebView::navigate(const std::string &url) {
  if (impl->webView == nullptr) {
    return;
  }

  webkit_web_view_load_uri(impl->webView, url.c_str());
}

void LinuxWebView::setFrontend(const std::string &path) {
  impl->frontendPath = path;
  impl->hasResources = false;
  impl->resourceManager.reset();
}

void LinuxWebView::setResources(Resources resources) {
  impl->resources = resources;
  impl->hasResources = true;

  impl->resourceManager = std::make_unique<ResourceManager>(resources);
}

void LinuxWebView::run() {
  if (impl->window != nullptr) {
    return;
  }

  impl->mainLoop = g_main_loop_new(nullptr, FALSE);

  impl->createWindow();
  impl->load();

  g_main_loop_run(impl->mainLoop);

  g_main_loop_unref(impl->mainLoop);
  impl->mainLoop = nullptr;
}

} // namespace lumi
