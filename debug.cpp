#include <config.h>
#include <debug.h>

#include <WiFi.h>

unsigned long elapsed = 0;

void debug_setup() {
  DEBUG_PORT.begin(DEBUG_BAUD);
  DEBUG_PORT.println("Connected!");
}

void debug_loop() {
  unsigned long m = millis();
  if (m - elapsed > DEBUG_DELAY) {
    elapsed = m;
    DEBUG_PORT.println("tick...");

//    DEBUG_PORT.printf("Stored SSID: %s\n", WiFi.SSID().c_str());
//    DEBUG_PORT.printf("WiFi mode: %d\n", WiFi.getMode());
//    DEBUG_PORT.printf("Connected: %s\n", WiFi.isConnected() ? "Yes" : "No");

    struct tm *timeInfo = controller_getTime();

    DEBUG_PORT.printf("%d-%d-%d %d:%d:%d\n",
      timeInfo->tm_year + 1900,
      timeInfo->tm_mon,
      timeInfo->tm_mday,
      timeInfo->tm_hour,
      timeInfo->tm_min,
      timeInfo->tm_sec);
  }
}
