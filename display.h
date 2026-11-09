#ifndef H_DISPLAY
#define H_DISPLAY

#include <config.h>

#include <Adafruit_Protomatter.h>

#define BRIGHT_H 255
#define BRIGHT_M 128
#define BRIGHT_L 80
#define BRIGHT_OFF 0

extern uint8_t brightness;

extern void display_setup();

extern void display_loop();

#endif