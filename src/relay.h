#ifndef RELAY__H
#define RELAY__H

#include <Arduino.h>

static const int RELAY_PIN = D3;

void handleStartRelay();
void handleRelaySchedule();
#endif