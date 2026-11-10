#ifndef H_STORAGE
#define H_STORAGE

#include <Arduino.h>

#define APP_PREFERENCES "matrix-display"

extern void storage_setBrightness(uint8_t brightness);

extern uint8_t storage_getBrightness(uint8_t defaultBrightness);

extern void storage_setStartTime();

extern void storage_setEndTime();

#endif