#include <config.h>
#include <debug.h>
#include <display.h>
#include <network.h>
#include <ui.h>
#include <WiFi.h>

int wifiStatus = WL_DISCONNECTED;

void setup() {
  debug_setup();
  display_setup();
  network_setup();
  ui_setup();
}

void loop() {
  int currentWifiStatus = WiFi.status();
  if (wifiStatus != currentWifiStatus) {
    DEBUG_PORT.println("wifi changed");
    wifiStatus = currentWifiStatus;
    // wifi status changed
    if (currentWifiStatus == WL_CONNECTED) {
      DEBUG_PORT.println("wifi connected");
      // wifi status is connected
      controller_syncTime();
    }
  }
  debug_loop();
  display_loop();
  network_loop();
  ui_loop();
}
