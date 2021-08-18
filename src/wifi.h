#ifndef WIFI__H
#define WIFI__H

static const char* WIFI_AP_NAME = "ESP-Timer";
static const char* WIFI_AP_PASSWORD = "12345678";

bool startWifi();
void handleWifi();
#endif