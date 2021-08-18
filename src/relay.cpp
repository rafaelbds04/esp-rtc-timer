#include <iostream>
#include <sstream>

#include <time.h>
#include "rtc.h"
#include "debug.h"
#include <ArduinoJson.h>
#include "local_storage.h"

const int RELAY_PIN = D7;
bool isRelayEnable = false;

time_t getTimeUnixFromString(std::string timestr)
{
  for (std::string::size_type pos = timestr.find(':'); pos != std::string::npos; pos = timestr.find(':', pos))
    timestr[pos] = ' ';
  std::stringstream iss_time(timestr);
  int hour, min, sec = 0;
  iss_time >> hour >> min >> sec;

  tm t;
  time_t now = getActualUnixtime();
  memcpy(&t, localtime(&now), sizeof(t));
  t.tm_hour = hour;
  t.tm_min = min;
  t.tm_sec = sec;
  return mktime(&t);
}

void handleStartRelay()
{
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);
}

void handleTurnRelayOn()
{
  digitalWrite(RELAY_PIN, LOW);
}

void handleTurnRelayOff()
{
  digitalWrite(RELAY_PIN, HIGH);
}

void handleRelaySchedule()
{
  time_t now = getActualUnixtime();

  isRelayEnable = false;
  for (JsonObject elem : getConfigJson().as<JsonArray>())
  {
    const char *timeStart = elem["timeStart"]; // "10:45:10", "10:45:10"
    const char *timeEnd = elem["timeEnd"];     // "10:45:10", "10:45:10"

    time_t t_hour_start = getTimeUnixFromString(timeStart);
    time_t t_hour_end = getTimeUnixFromString(timeEnd);

    JsonArray days = elem["days"];
    for (JsonVariant v : days)
    {
      if (v.as<int>() == getActualDateTime().dayOfTheWeek() &&
          (t_hour_start <= now) && (now <= t_hour_end))
      {
        isRelayEnable = true;
      }
    }
  }

  if (isRelayEnable)
  {
    handleTurnRelayOn();
  }
  else
  {
    handleTurnRelayOff();
  }
}