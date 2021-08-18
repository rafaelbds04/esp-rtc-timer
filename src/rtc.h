#ifndef RTC__H
#define RTC__H

#include <Arduino.h>
#include "RTClib.h"

static const int RTC_SDA_PIN = D2;
static const int RTC_SCL_PIN = D3;

//starts rtc
void startRtc();
//get unixtime from rtc
time_t getActualUnixtime();
DateTime getActualDateTime();
String getDateISOString();
void setDateTime(const char *date);
#endif