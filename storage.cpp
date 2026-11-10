#include <storage.h>

#include <Preferences.h>

Preferences preferences;

void storage_setBrightness(uint8_t brightness) {
  preferences.begin(APP_PREFERENCES, false); // false = read/write
  preferences.putUChar("brightness", brightness);
  preferences.end();
}

uint8_t storage_getBrightness(uint8_t defaultBrightness) {
  preferences.begin(APP_PREFERENCES, true); // true = read only
  uint8_t result = preferences.getUChar("brightness", defaultBrightness);
  preferences.end();
  return result;
}

void storage_setStartTime() {
  preferences.begin(APP_PREFERENCES, false); // false = read/write
  //preferences.put?("startTime", startTime);
  preferences.end();
}

void storage_setEndTime() {
  preferences.begin(APP_PREFERENCES, false); // false = read/write
  //preferences.put?("endTime", startTime);
  preferences.end();
}
