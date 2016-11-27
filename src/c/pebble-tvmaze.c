#include <pebble.h>
#include "modules/comm.h"
#include "modules/settings.h"
#include "windows/main_window.h"

static void prv_init(void) {
  comm_init();
  prv_load_settings();
  prv_window_push();
}

static void prv_deinit(void) {
  comm_deinit();
}

int main(void) {
  prv_init();
  app_event_loop();
  prv_deinit();
}
