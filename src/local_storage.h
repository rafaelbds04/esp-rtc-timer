#ifndef LOCAL_STORAGE__H
#define LOCAL_STORAGE__H

#include <Arduino.h>
#include <ArduinoJson.h>

extern StaticJsonDocument<1024> config;

char *getConfig();
bool saveConfig(ArduinoJson6180_91::StaticJsonDocument<1024U> doc);
ArduinoJson6180_91::StaticJsonDocument<1024U> getConfigJson();
void setupStorage();
#endif