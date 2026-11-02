#ifndef H_CONTROLLER_PORTALM4
#define H_CONTROLLER_PORTALM4

#include <stdint.h>
#include <Adafruit_Protomatter.h>

// Matrix dimensions
#define BIT_DEPTH       4    // Color depth (1 to 6)
#define PANEL_WIDTH     64   // Individual module width in pixels
#define PANEL_HEIGHT    32   // Individual module height in pixels

// Hardware pin mapping
#define MATRIX_CLK_PIN  -1
#define MATRIX_LAT_PIN  -1
#define MATRIX_OE_PIN   -1

extern Adafruit_Protomatter matrixM4;

extern void controllerM4_setup();

extern void controllerM4_syncTime();

extern void controllerM4_setTime(struct tm timeInfo);

extern tm* controllerM4_getTime();

extern bool controllerM4_hasTime();

#endif