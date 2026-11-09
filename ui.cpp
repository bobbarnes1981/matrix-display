#include <ui.h>
#include <debug.h>
#include <display.h>

#include <ESPUI.h>

void brightnessCallback(Control *sender, int type) {
  DEBUG_PORT.print("Selected value ");
  DEBUG_PORT.println(sender->value);
  if (sender->value == "H") {
    brightness = BRIGHT_H;
  } else if (sender->value == "M") {
    brightness = BRIGHT_M;
  } else if (sender->value == "L") {
    brightness = BRIGHT_L;
  } else if (sender->value == "O") {
    brightness = BRIGHT_OFF;
  }
}

void ui_setup() {
  uint16_t mainTab = ESPUI.addControl(ControlType::Tab, "Settings", "Settings");

  uint16_t brightnessDropdown = ESPUI.addControl(
    ControlType::Select,
    "Choose brightness",
    "Brightness",
    ControlColor::Alizarin,
    mainTab,
    brightnessCallback
  );

  ESPUI.addControl(ControlType::Option, "Bright", "H", ControlColor::Alizarin, brightnessDropdown);
  ESPUI.addControl(ControlType::Option, "Normal", "M", ControlColor::Alizarin, brightnessDropdown);
  ESPUI.addControl(ControlType::Option, "Dim", "L", ControlColor::Alizarin, brightnessDropdown);
  ESPUI.addControl(ControlType::Option, "Off", "O", ControlColor::Alizarin, brightnessDropdown);

  ESPUI.begin("Matrix Display");
}

void ui_loop() {

}
