#include <ui.h>
#include <debug.h>
#include <display.h>
#include <storage.h>

#include <ESPUI.h>

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
  } else if (sender->value == "0") {
    brightness = BRIGHT_0;
  }

  storage_setBrightness(brightness);
}

void startTimeCallback(Control *sender, int type) {
  DEBUG_PORT.print("Selected value ");
  DEBUG_PORT.println(sender->value);
  storage_setStartTime();
}

void endTimeCallback(Control *sender, int type) {
  DEBUG_PORT.print("Selected value ");
  DEBUG_PORT.println(sender->value);
  storage_setEndTime();
}

void ui_setup() {
  uint16_t mainTab = ESPUI.addControl(ControlType::Tab, "Settings", "Settings");

  uint16_t brightnessControl = ESPUI.addControl(
    ControlType::Select,
    "Brightness",
    "80", // TODO: this should be the value loaded from storage
    ControlColor::Alizarin,
    mainTab,
    brightnessCallback
  );

  ESPUI.addControl(ControlType::Option, "255", "255", ControlColor::Alizarin, brightnessControl);
  ESPUI.addControl(ControlType::Option, "128", "128", ControlColor::Alizarin, brightnessControl);
  ESPUI.addControl(ControlType::Option, "80", "80", ControlColor::Alizarin, brightnessControl);
  ESPUI.addControl(ControlType::Option, "Off", "0", ControlColor::Alizarin, brightnessControl);

  uint16_t startTimeControl = ESPUI.addControl(
    ControlType::Text,
    "Start time",
    "06:00",
    ControlColor::Alizarin,
    mainTab,
    startTimeCallback
  );
  ESPUI.setInputType(startTimeControl, "time");
  
  uint16_t endTimeControl = ESPUI.addControl(
    ControlType::Text,
    "End time",
    "22:00",
    ControlColor::Alizarin,
    mainTab,
    endTimeCallback
  );
  ESPUI.setInputType(endTimeControl, "time");

  ESPUI.begin("Matrix Display");
}

void ui_loop() {

}
