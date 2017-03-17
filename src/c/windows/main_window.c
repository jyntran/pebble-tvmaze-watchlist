#include "main_window.h"

static Window *s_window;

static TextLayer *s_test_layer;
static char show[64];

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  // Begin dictionary
  DictionaryIterator *iter;
  app_message_outbox_begin(&iter);

  // Add a key-value pair
  dict_write_uint8(iter, 0, 0);

  // Send the message!
  app_message_outbox_send();
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
}

static void prv_window_load(Window *window) {
	Layer *s_window_layer = window_get_root_layer(window);
	GRect bounds = layer_get_bounds(s_window_layer);

	/* add screen elements here */
	s_test_layer = text_layer_create(GRect(0, 0, bounds.size.w, 50));
	text_layer_set_text(s_test_layer, show);
	layer_add_child(s_window_layer, text_layer_get_layer(s_test_layer));
}

static void prv_window_unload(Window *window) {
  if (s_window) { window_destroy(s_window); }
}

void prv_window_push() {
  if (!s_window) {
    s_window = window_create();
    window_set_click_config_provider(s_window, click_config_provider);
    window_set_window_handlers(s_window, (WindowHandlers) {
      .load = prv_window_load,
      .unload = prv_window_unload,
    });
  }
  window_stack_push(s_window, true);
}

void prv_window_update() {
  APP_LOG(APP_LOG_LEVEL_INFO, "showid = %d", data_get_array_value(0));
  //APP_LOG(APP_LOG_LEVEL_INFO, "showname = %s", (char *)data_get_array_value(1));
//  snprintf(show, sizeof(show), "Show ID: %d - Show Name: %d", data_get_array_value(0), (char *)data_get_array_value(1));
  snprintf(show, sizeof(show), "Show ID: %d", data_get_array_value(0));
  text_layer_set_text(s_test_layer, show);
}