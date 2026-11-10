#include <ui.h>
#include <debug.h>
#include <display.h>

#include <ESPUI.h>

void brightnessCallback(Control *sender, int type) {
  DEBUG_PORT.print("Selected value ");
  DEBUG_PORT.println(sender->value);
  if (sender->value == "255") {
    brightness = BRIGHT_255;
  } else if (sender->value == "128") {
    brightness = BRIGHT_128;
  } else if (sender->value == "80") {
    brightness = BRIGHT_80;
  } else if (sender->value == "O") {
    brightness = BRIGHT_0;
  }
}

void ui_setup() {
  uint16_t mainTab = ESPUI.addControl(ControlType::Tab, "Settings", "Settings");

  uint16_t brightnessDropdown = ESPUI.addControl(
    ControlType::Select,
    "Choose brightness",
    "80",
    ControlColor::Alizarin,
    mainTab,
    brightnessCallback
  );

  ESPUI.addControl(ControlType::Option, "255", "255", ControlColor::Alizarin, brightnessDropdown);
  ESPUI.addControl(ControlType::Option, "128", "128", ControlColor::Alizarin, brightnessDropdown);
  ESPUI.addControl(ControlType::Option, "80", "80", ControlColor::Alizarin, brightnessDropdown);
  ESPUI.addControl(ControlType::Option, "Off", "0", ControlColor::Alizarin, brightnessDropdown);

  ESPUI.begin("Matrix Display");
}

void ui_loop() {

}
