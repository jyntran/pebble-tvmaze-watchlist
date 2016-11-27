#include "main_window.h"

static Window *s_window;

static void prv_window_load(Window *window) {
}

static void prv_window_unload(Window *window) {
  if (s_window) { window_destroy(s_window); }
}

void prv_window_push() {
  if (!s_window) {
    s_window = window_create();
    window_set_window_handlers(s_window, (WindowHandlers) {
      .load = prv_window_load,
      .unload = prv_window_unload,
    });
  }
  window_stack_push(s_window, true);
}
