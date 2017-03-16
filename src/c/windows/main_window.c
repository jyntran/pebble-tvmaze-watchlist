#include "main_window.h"

static Window *s_window;

static TextLayer *s_test_layer;
static char show[64];

static void prv_window_load(Window *window) {
	Layer *window_layer = window_get_root_layer(window);
	GRect bounds = layer_get_bounds(window_layer);

  APP_LOG(APP_LOG_LEVEL_INFO, "LOADING");

  snprintf(show, sizeof(show), "Show ID: %d", data_get_array_value(0));

	/* add screen elements here */
	s_test_layer = text_layer_create(GRect(0, 0, bounds.size.w, 50));
	text_layer_set_text(s_test_layer, show);
	layer_add_child(window_layer, text_layer_get_layer(s_test_layer));
  APP_LOG(APP_LOG_LEVEL_INFO, "LOADED");
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
