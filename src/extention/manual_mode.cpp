#include "../../lib/watering_unit.h"

void manualControl() {
    if (M5.BtnA.wasPressed()) {
        manualMode = !manualMode;
        M5.Lcd.fillScreen(BLACK);
        M5.Lcd.setCursor(10, 10);
        if (manualMode) {
            M5.Lcd.println("Manual mode ON");
        } else {
            M5.Lcd.println("Manual mode OFF");
        }
    }

    if (manualMode) {
        if (M5.BtnB.wasPressed()) {
            manualPumpState = !manualPumpState;
            digitalWrite(PUMP_PIN, manualPumpState ? HIGH : LOW);
            M5.Lcd.setCursor(10, 50);
            if (manualPumpState) {
                M5.Lcd.println("Pump ON");
            } else {
                M5.Lcd.println("Pump OFF");
            }
        }
    }
}