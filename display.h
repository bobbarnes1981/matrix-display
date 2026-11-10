#ifndef H_DISPLAY
#define H_DISPLAY

#include <config.h>

#include <Adafruit_Protomatter.h>

#define BRIGHT_255 255
#define BRIGHT_128 128
#define BRIGHT_80 80
#define BRIGHT_0 0

extern uint8_t brightness;

extern void display_setup();

extern void display_loop();

#endif