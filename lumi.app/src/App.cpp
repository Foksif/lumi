#include <lumi/app/App.hpp>

#include <lumi/webview/WebViewModule.hpp>

namespace lumi {

App::App() { WebViewModule::initialize(); }

App::~App() { WebViewModule::shutdown(); }

WebView &App::webView() { return view; }

void App::run() { view.run(); }

} // namespace lumi
