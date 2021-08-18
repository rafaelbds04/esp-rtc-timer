#include "wifi.h"
#include "debug.h"
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiManager.h>

WiFiManager wifiManager;

bool startWifi()
{
  DEBUG_INFO("[startWifi] begin");

  //Timeout to wifi setup, this avoid to application break
  wifiManager.setConfigPortalTimeout(180);

  if (wifiManager.autoConnect("ESP-Timer", "12345678"))
  {
    DEBUG_WARNING("connected...yeey :)");
  }
  else
  {
    DEBUG_WARNING("Configportal running");
  }

  DEBUG_INFO("[startWifi] end");
  return true;
}