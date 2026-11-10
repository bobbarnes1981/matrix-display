#include <ui.h>
#include <debug.h>
#include <display.h>

#include <ESPUI.h>
#include <Preferences.h>

Preferences preferences;

void brightnessCallback(Control *sender, int type) {
  DEBUG_PORT.print("Selected value ");
  DEBUG_PORT.println(sender->value);
  // TODO: convert to number instead of switch
  if (sender->value == "255") {
    brightness = BRIGHT_255;
  } else if (sender->value == "128") {
    brightness = BRIGHT_128;
  } else if (sender->value == "80") {
    brightness = BRIGHT_80;
  } else if (sender->value == "O") {
    brightness = BRIGHT_0;
  }

  preferences.begin(APP_PREFERENCES, false); // false = read/write
  preferences.putUInt("brightness", brightness);
  preferences.end();
}

void startTimeCallback(Control *sender, int type) {
  DEBUG_PORT.print("Selected value ");
  DEBUG_PORT.println(sender->value);



  //preferences.begin(APP_PREFERENCES, false); // false = read/write
  //preferences.putUInt("startTime", startTime);
  //preferences.end();
}

void endTimeCallback(Control *sender, int type) {
  DEBUG_PORT.print("Selected value ");
  DEBUG_PORT.println(sender->value);



  //preferences.begin(APP_PREFERENCES, false); // false = read/write
  //preferences.putUInt("endTime", startTime);
  //preferences.end();
}

void ui_setup() {
  uint16_t mainTab = ESPUI.addControl(ControlType::Tab, "Settings", "Settings");

  uint16_t brightnessControl = ESPUI.addControl(
    ControlType::Select,
    "Brightness",
    "80",
    ControlColor::Alizarin,
    mainTab,
    brightnessCallback
  );

  ESPUI.addControl(ControlType::Option, "255", "255", ControlColor::Alizarin, brightnessControl);
  ESPUI.addControl(ControlType::Option, "128", "128", ControlColor::Alizarin, brightnessControl);
  ESPUI.addControl(ControlType::Option, "80", "80", ControlColor::Alizarin, brightnessControl);
  ESPUI.addControl(ControlType::Option, "Off", "0", ControlColor::Alizarin, brightnessControl);

  uint16_t startTimeControl = ESPUI.addControl(
    ControlType::Time,
    "Start time",
    "06:00",
    ControlColor::Alizarin,
    mainTab,
    startTimeCallback
  );

  uint16_t endTimeControl = ESPUI.addControl(
    ControlType::Time,
    "End time",
    "20:00",
    ControlColor::Alizarin,
    mainTab,
    endTimeCallback
  );

  ESPUI.begin("Matrix Display");
}

void ui_loop() {

}
