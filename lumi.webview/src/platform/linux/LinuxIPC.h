#pragma once

#include <jsc/jsc.h>
#include <stddef.h>
#include <webkit/webkit.h>

void lumi_ipc_to_js(WebKitWebView *webView, const char *script);

void lumi_ipc_from_js(WebKitWebView *webView,
                      void (*callback)(const char *data, size_t size));

void handler(WebKitUserContentManager *manager, JSCValue *value,
             gpointer userData);
