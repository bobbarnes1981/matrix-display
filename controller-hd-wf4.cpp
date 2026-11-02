#include <controller-hd-wf4.h>
#include <debug.h>

#include <Arduino.h>
#include <Adafruit_Protomatter.h>

const char *ntpServer = "pool.ntp.org";
const long gmtOffset = 0;
const int daylightOffset = 3600;

extern uint8_t rgbPins[] = {
  WF4_X1_R1_PIN, WF4_X1_G1_PIN, WF4_X1_B1_PIN,
  WF4_X1_R2_PIN, WF4_X1_G2_PIN, WF4_X1_B2_PIN
};

extern uint8_t addrPins[] = {
  WF4_A_PIN, WF4_B_PIN, WF4_C_PIN, WF4_D_PIN // Include WF4_E_PIN here if utilizing 1/32 scan panels
};

// Initialize the Protomatter Matrix
extern Adafruit_Protomatter matrix(
  PANEL_WIDTH,          // Width of matrix grid
  BIT_DEPTH,            // Color bit depth
  1, rgbPins,           // Number of parallel matrices (usually 1), RGB pins array
  sizeof(addrPins),     // Number of address lines
  addrPins,             // Address pins array
  MATRIX_CLK_PIN,       // Clock pin
  MATRIX_LAT_PIN,       // Latch pin
  MATRIX_OE_PIN,        // Output Enable pin
  true                  // Enable double-buffering for smooth animation
);

void controllerWF4_setup() {
  // CRITICAL STEP FOR HD-WF4: Set the hardware port output enable line high
  pinMode(WF4_PORT_X1_X2_EN, OUTPUT);
  digitalWrite(WF4_PORT_X1_X2_EN, HIGH);

  // Initialize the matrix
  ProtomatterStatus status = matrix.begin();
  
  if (status != PROTOMATTER_OK) {
    Serial.println("Protomatter initialization failed!");
    while(1); 
  }
  
  Serial.println("Matrix initialized successfully!");
}

void controllerWF4_syncTime() {
  configTime(gmtOffset, daylightOffset, ntpServer);
  DEBUG_PORT.println("Configured time");

  struct tm timeInfo;
  if (!getLocalTime(&timeInfo, 5000)) {
    DEBUG_PORT.println("Failed to get ntp time");
  } else {
    DEBUG_PORT.println("Synced ntp time");
    DEBUG_PORT.printf("%d-%d-%d %d:%d:%d\n", timeInfo.tm_year + 1900, timeInfo.tm_mon, timeInfo.tm_mday, timeInfo.tm_hour, timeInfo.tm_min, timeInfo.tm_sec);

    controllerWF4_setTime();
  }
}

void controllerWF4_setTime() {
  // todo: store time in RTC
}

void controllerWF4_getTime() {
  // todo: get time from RTC 
}
