#include <display.h>
#include <ui.h>

#include <Adafruit_Protomatter.h>
#include <Adafruit_GFX.h>
#include <Fonts/TomThumb.h>
#include <Preferences.h>
#include <WiFi.h>

int mode = 0;

uint8_t brightness = BRIGHT_80;
// startTime = 06:00;
// endTime = 20:00;

int angle = 0;
unsigned long angleSpeed = 11;
unsigned long lastElapsed = 0;

/**
 * Generates an RGB565 color from a 360-degree color wheel angle.
 * @param angle Integer from 0 to 359 representing the position on the wheel.
 * @return uint16_t The packed RGB565 color value.
 */
uint16_t get_rgb565_color_wheel(int angle) {
    // Normalize angle to 0-359 range just in case
    angle = angle % 360;
    if (angle < 0) angle += 360;

    uint8_t r = 0, g = 0, b = 0;
    int section = angle / 60;       // 6 sections of 60 degrees
    int remainder = angle % 60;     // Position within the section
    uint8_t v = (remainder * 255) / 60; // Scale remainder to 0-255 range

    switch (section) {
        case 0: r = 255;     g = v;       b = 0;       break; // Red to Yellow
        case 1: r = 255 - v; g = 255;     b = 0;       break; // Yellow to Green
        case 2: r = 0;       g = 255;     b = v;       break; // Green to Cyan
        case 3: r = 0;       g = 255 - v; b = 255;     break; // Cyan to Blue
        case 4: r = v;       g = 0;       b = 255;     break; // Blue to Magenta
        case 5: r = 255;     g = 0;       b = 255 - v; break; // Magenta to Red
    }

    r = ((uint16_t)r * brightness) >> 8;
    g = ((uint16_t)g * brightness) >> 8;
    b = ((uint16_t)b * brightness) >> 8;

    // Convert 8-bit R, G, B to RGB565 bit-packed format
    // Red:   5 bits (shift right by 3, shift left to bits 11-15)
    // Green: 6 bits (shift right by 2, shift left to bits 5-10)
    // Blue:  5 bits (shift right by 3, shift left to bits 0-4)
    return (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3));
}

void incremenetAngle() {
  angle+=1;
  if (angle >= 360) {
    angle = 0;
  }
}

int getAngleOffset(int offset) {
  if (offset >= 720) {
    return 0;
  }
  if (angle + offset >= 360) {
    return angle + offset - 360;
  }
  return angle + offset;
}

void display_setup() {
  controller_setup();

  preferences.begin(APP_PREFERENCES, true); // true = read only

  brightness = preferences.getUInt("brightness", BRIGHT_80);
//  startTime = preferences.getUInt("startTime", 06:00);
//  endTime = preferences.getUInt("endTime", 22:00);

  preferences.end();

}

void drawDefault() {
  matrix.drawRect(0, 0, matrix.width(), matrix.height(), matrix.color565(255, 0, 0)); // Red border

  matrix.drawCircle(matrix.width() / 2, matrix.height() / 2, 10, matrix.color565(0, 0, 255)); // Blue center circle
  
  matrix.setCursor(5, 12);
  matrix.setFont();
  matrix.setTextColor(matrix.color565(0, 255, 0)); // Green text
  matrix.print("Matrix...");
}

void drawAPIP() {
  matrix.setCursor(2, 24);
  matrix.setFont(&TomThumb);
  matrix.setTextColor(matrix.color565(255, 0, 0)); // Red text
  matrix.print(WiFi.softAPIP());
}

void drawLocalIP() {
  matrix.setCursor(2, 24);
  matrix.setFont(&TomThumb);
  matrix.setTextColor(get_rgb565_color_wheel(getAngleOffset(270)));
  matrix.print(WiFi.localIP());
}

void drawTime() {
  matrix.drawRect(0, 0, matrix.width(), matrix.height(), get_rgb565_color_wheel(getAngleOffset(0)));

  struct tm *timeInfo = controller_getTime();

  matrix.setCursor(2, 10);
  matrix.setFont();
  matrix.setTextColor(get_rgb565_color_wheel(getAngleOffset(90)));
  matrix.printf("%d-%02d-%02d",
      timeInfo->tm_year + 1900,
      timeInfo->tm_mon + 1,
      timeInfo->tm_mday);

  matrix.setCursor(8, 15);
  matrix.setFont();
  matrix.setTextColor(get_rgb565_color_wheel(getAngleOffset(180)));
  matrix.printf("%02d:%02d:%02d",
      timeInfo->tm_hour,
      timeInfo->tm_min,
      timeInfo->tm_sec);

  drawLocalIP();
}

void drawCountdown() {

}

void display_loop() {
  unsigned long m = millis();
  if (m - lastElapsed > angleSpeed) {
    lastElapsed = m;
    incremenetAngle();
  }

  if (WiFi.status() != WL_CONNECTED) {
    matrix.setCursor(5, 12);
    matrix.setFont();
    matrix.setTextColor(matrix.color565(0, 255, 0)); // Green text
    matrix.print("WiFi");

    drawAPIP();

    matrix.show();
  } else {
    /*
     * TODO: check startTime and endTime
     *       if within range show display
     *       otherwise maybe only show every 30 seconds, or just show ip address?
     */

    // Clear the screen buffer
    matrix.fillScreen(matrix.color565(0, 0, 0));

    switch (mode) {
      case 0: // clock
        {
          if (controller_hasTime()) {
            drawTime();
          } else {
            drawDefault();
          }
        }
        break;

      case 1: // countdown
        {
          if (controller_hasTime()) {
            drawCountdown();
          } else {
            drawDefault();
          }
        }
        break;
    }

    // Push buffer to the physical panel
    matrix.show();
  }
}