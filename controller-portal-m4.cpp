#include <controller-portal-m4.h>
#include <debug.h>

#include <Arduino.h>
#include <Adafruit_Protomatter.h>
#include <time.h>

uint8_t rgbPinsM4[] = {
};

uint8_t addrPinsM4[] = {
};

// Initialize the Protomatter Matrix
Adafruit_Protomatter matrixM4(
  PANEL_WIDTH,          // Width of matrix grid
  BIT_DEPTH,            // Color bit depth
  1, rgbPinsM4,         // Number of parallel matrices (usually 1), RGB pins array
  sizeof(addrPinsM4),   // Number of address lines
  addrPinsM4,           // Address pins array
  MATRIX_CLK_PIN,       // Clock pin
  MATRIX_LAT_PIN,       // Latch pin
  MATRIX_OE_PIN,        // Output Enable pin
  true                  // Enable double-buffering for smooth animation
);

struct tm lastTimeM4;
unsigned long lastMillisM4 = 0;

void controllerM4_setup() {
  // Initialize the matrix
  ProtomatterStatus status = matrixM4.begin();
  
  if (status != PROTOMATTER_OK) {
    Serial.println("Protomatter initialization failed!");
    while(1); 
  }
  
  Serial.println("Matrix initialized successfully!");
}

void controllerM4_syncTime() {

}

void controllerM4_setTime(tm timeInfo) {
  // store ntp time and elapsed millis
  lastTimeM4 = timeInfo;
  lastMillisM4 = millis();
}

struct tm* controllerM4_getTime() {
  // get timestamp, calculate new timestamp
  time_t totalSeconds = mktime(&lastTimeM4);
  time_t t = totalSeconds + ((millis() - lastMillisM4)/1000);

  // convert to tm struct
  return gmtime(&t);
}

bool controllerM4_hasTime() {
  return lastMillisM4 != 0;
}
