#include "LinuxWebViewModule.hpp"

#include <gtk/gtk.h>

namespace lumi {

namespace {

bool initialized = false;

}

void LinuxWebViewModule::initialize() {
  if (initialized) {
    return;
  }

  gtk_init();

  initialized = true;
}

void LinuxWebViewModule::shutdown() { initialized = false; }

} // namespace lumi
