#include "settings.h"

static void prv_default_settings() {
  strcpy(settings.ApiKey, "apiKey\0");
}

static void prv_save_settings() {
  persist_write_data(SETTINGS_KEY, &settings, sizeof(settings));
}

static void prv_inbox_received_handler(DictionaryIterator *iter, void *context) {
  Tuple *apikey_tuple = dict_find(iter, MESSAGE_KEY_ApiKey);
  if (apikey_tuple) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "ApiKey found: %s", apikey_tuple->value->cstring);
    strcpy(settings.ApiKey, (char*)apikey_tuple->value->cstring);
    APP_LOG(APP_LOG_LEVEL_DEBUG, "ApiKey set: %s", settings.ApiKey);
  }

  prv_save_settings();
}

void prv_load_settings() {
  prv_default_settings();
  persist_read_data(SETTINGS_KEY, &settings, sizeof(settings));

  app_message_register_inbox_received(prv_inbox_received_handler);
  app_message_open(128, 128);
}

