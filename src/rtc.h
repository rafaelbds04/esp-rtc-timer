#ifndef RTC__H
#define RTC__H

#include <Arduino.h>
#include "RTClib.h"

//starts rtc
void startRtc();
//get unixtime from rtc
time_t getActualUnixtime();
DateTime getActualDateTime();
String getDateISOString();
void setDateTime(const char *date);
#endif