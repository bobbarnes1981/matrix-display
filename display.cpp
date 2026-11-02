#include <display.h>

#include <Adafruit_Protomatter.h>
#include <WiFi.h>

int mode = 0;

void display_setup() {
  controller_setup();
}

void drawDefault() {
  matrix.drawRect(0, 0, matrix.width(), matrix.height(), matrix.color565(255, 0, 0)); // Red border

  matrix.drawCircle(matrix.width() / 2, matrix.height() / 2, 10, matrix.color565(0, 0, 255)); // Blue center circle
  
  matrix.setCursor(5, 12);
  matrix.setTextColor(matrix.color565(0, 255, 0)); // Green text
  matrix.print("Matrix...");
}

void drawTime() {
  matrix.drawRect(0, 0, matrix.width(), matrix.height(), matrix.color565(0, 0, 255)); // Blue border

  struct tm *timeInfo = controller_getTime();

  matrix.setTextColor(matrix.color565(0, 255, 0)); // Green text
  matrix.setCursor(2, 7);
  matrix.printf("%d-%02d-%02d",
      timeInfo->tm_year + 1900,
      timeInfo->tm_mon,
      timeInfo->tm_mday);

  matrix.setTextColor(matrix.color565(255, 0, 0)); // Red text
  matrix.setCursor(2, 18);
  matrix.printf("%02d:%02d:%02d",
      timeInfo->tm_hour,
      timeInfo->tm_min,
      timeInfo->tm_sec);
}

void drawCountdown() {

}

void display_loop() {
  if (WiFi.status() != WL_CONNECTED) {
    matrix.setCursor(5, 12);
    matrix.setTextColor(matrix.color565(0, 255, 0)); // Green text
    matrix.print("WiFi");
    matrix.show();
  } else {
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