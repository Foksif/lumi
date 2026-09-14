#include <lumi/webview/WebViewModule.hpp>

#include "platform/linux/LinuxWebViewModule.hpp"

namespace lumi {

void WebViewModule::initialize() { LinuxWebViewModule::initialize(); }

void WebViewModule::shutdown() { LinuxWebViewModule::shutdown(); }

} // namespace lumi
