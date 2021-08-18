#include "rtc.h"

#include "debug.h"
#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc;

void startRtc()
{
    Wire.begin(RTC_SDA_PIN, RTC_SCL_PIN);
    if (!rtc.begin())
    {                                        
        DEBUG_WARNING("RTC NOT INITIALIZED");
        while (1); //Break
    }
    delay(100);
}

time_t getActualUnixtime()
{
    return rtc.now().unixtime();
}

DateTime getActualDateTime()
{
    return rtc.now();
}

String getDateISOString()
{
    return rtc.now().timestamp(DateTime::TIMESTAMP_FULL);
}

void setDateTime(const char *date)
{
    rtc.adjust(DateTime(date));
}