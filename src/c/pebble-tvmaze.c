#include <pebble.h>
#include "windows/main_window.h"

static void prv_init(void) {
  prv_load_settings();
  prv_window_push();
}

static void prv_deinit(void) {}

int main(void) {
  prv_init();
  app_event_loop();
  prv_deinit();
}
