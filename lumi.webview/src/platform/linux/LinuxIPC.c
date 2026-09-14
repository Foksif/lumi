#include "./LinuxIPC.h"

struct IPCContext {
  void (*callback)(const char *data, size_t size);
};

void lumi_ipc_to_js(WebKitWebView *webView, const char *script) {
  webkit_web_view_evaluate_javascript(webView, script, -1, NULL, NULL, NULL,
                                      NULL, NULL);
};

void lumi_ipc_from_js(WebKitWebView *webView,
                      void (*callback)(const char *data, size_t size)) {
  WebKitUserContentManager *manager =
      webkit_web_view_get_user_content_manager(webView);

  webkit_user_content_manager_register_script_message_handler(manager, "lumi",
                                                              NULL);

  struct IPCContext *context = malloc(sizeof(struct IPCContext));

  context->callback = callback;

  g_signal_connect(manager, "script-message-received::lumi",
                   G_CALLBACK(handler), context);
}

void handler(WebKitUserContentManager *manager, JSCValue *value,
             gpointer userData) {
  struct IPCContext *context = userData;

  char *message = jsc_value_to_string(value);

  context->callback(message, strlen(message));

  g_free(message);
}
