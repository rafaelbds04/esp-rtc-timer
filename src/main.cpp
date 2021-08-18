#include <Arduino.h>

#include "debug.h"
#include "wifi.h" //startWifi();
#include "rtc.h"  //startRtc
#include "web_server.h"
#include "relay.h"
#include "local_storage.h"

void setup()
{
  DEBUG_BEGIN;
  DEBUG_INFO("[setup] begin");
  setupStorage();
  startRtc();
  handleStartRelay();

  startWifi();
  startWebServer();

  DEBUG_INFO("[setup] end");
}

void loop()
{
  handleWebServer();
  handleRelaySchedule();
}