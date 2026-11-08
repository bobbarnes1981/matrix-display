#include <ui.h>
#include <debug.h>
#include <display.h>

#include <ESPUI.h>

void brightnessCallback(Control *sender, int type) {
  DEBUG_PORT.print("Selected value ");
  DEBUG_PORT.println(sender->value);
  if (sender->value == "H") {
    brightness = 255;
  } else if (sender->value == "M") {
    brightness = 128;
  } else if (sender->value == "L") {
    brightness = 80;
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

  ESPUI.begin("ESPUI testing");
}

void ui_loop() {

}
