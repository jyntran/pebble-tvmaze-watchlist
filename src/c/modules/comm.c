#include "comm.h"

static void inbox_received_handler(DictionaryIterator *iter, void *context) {

  APP_LOG(APP_LOG_LEVEL_INFO, "Message received!");

  Tuple *js_ready_t = dict_find(iter, MESSAGE_KEY_JSReady);
  if (js_ready_t) {
    APP_LOG(APP_LOG_LEVEL_INFO, "JS Ready");
  }

  Tuple *apikey_tuple = dict_find(iter, MESSAGE_KEY_ApiKey);
  if (apikey_tuple) {
    strcpy(settings.ApiKey, (char*)apikey_tuple->value->cstring);
  }

// Store incoming information
static char showid_buffer[8];
static char showname_buffer[64];
static char show_buffer[64];

// Read data
Tuple *showid_tuple = dict_find(iter, MESSAGE_KEY_SHOWID);
Tuple *showname_tuple = dict_find(iter, MESSAGE_KEY_SHOWNAME);

// If data, use it
if (showid_tuple) {
  snprintf(showid_buffer, sizeof(showid_buffer), "%d", (int)showid_tuple->value->int32);
  //snprintf(showname_buffer, sizeof(showname_buffer), "%s", showname_tuple->value->cstring);

  // Assemble full string then display
  //snprintf(show_buffer, sizeof(show_buffer), "%s, %s", showid_buffer, showname_buffer);

  // Test data module
  data_set_array_value(0, (int)showid_tuple->value->int32);
  APP_LOG(APP_LOG_LEVEL_INFO, "Get data: show id is %d", data_get_array_value(0));

  //data_set_array_value(1, (int)showname_tuple->value->cstring);
  //APP_LOG(APP_LOG_LEVEL_INFO, "Get data: show name is %d", data_get_array_value(1));
}

  prv_save_settings();
  prv_window_update();
}

static void inbox_dropped_handler(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped!");
}

static void outbox_failed_handler(DictionaryIterator *iterator, AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Outbox send failed!");
}

static void outbox_sent_handler(DictionaryIterator *iterator, void *context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Outbox send success!");
}


void comm_init() {
  app_message_register_inbox_received(inbox_received_handler);
  app_message_register_inbox_dropped(inbox_dropped_handler);
  app_message_register_outbox_failed(outbox_failed_handler);
  app_message_register_outbox_sent(outbox_sent_handler);

  const int inbox_size = 128;
  const int outbox_size = 128;
  app_message_open(inbox_size, outbox_size);
}

void comm_deinit() { 
  // Nothing yet
}

