#ifndef H_CONTROLLER_HDWF4
#define H_CONTROLLER_HDWF4

#include <stdint.h>
#include <Adafruit_Protomatter.h>

// Matrix dimensions for a single panel connected to Port 1 (X1)
#define BIT_DEPTH       4    // Color depth (1 to 6)
#define PANEL_WIDTH     64   // Individual module width in pixels
#define PANEL_HEIGHT    32   // Individual module height in pixels

// Hardware pin mapping specific to Huidu HD-WF4 (ESP32-S3)
#define MATRIX_CLK_PIN  34
#define MATRIX_LAT_PIN  33
#define MATRIX_OE_PIN   35

#define WF4_A_PIN       39
#define WF4_B_PIN       38
#define WF4_C_PIN       37
#define WF4_D_PIN       36
#define WF4_E_PIN       21   // Set to -1 if using 1/16 scan panels (A,B,C,D only)

// Port 1 (X1) Data Pins
#define WF4_X1_R1_PIN   2
#define WF4_X1_B1_PIN   6
#define WF4_X1_G1_PIN   10
#define WF4_X1_R2_PIN   3
#define WF4_X1_B2_PIN   7
#define WF4_X1_G2_PIN   11

// Port Selection Enable Pins (HD-WF4 uses these pins to switch between physical ports)
#define WF4_PORT_X1_X2_EN  45
#define WF4_PORT_X3_X4_EN  14

extern uint8_t rgbPins[];

extern uint8_t addrPins[];

extern Adafruit_Protomatter matrix;

extern void controllerWF4_setup();

extern void controllerWF4_syncTime();

extern void controllerWF4_setTime();

extern void controllerWF4_getTime();

#endif