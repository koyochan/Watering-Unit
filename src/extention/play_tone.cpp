# include "../../lib/watering_unit.h"

void playTone() {
    for (int i = 0; i < sizeof(tone_data) / sizeof(tone_data[0]); i++) {
        M5.Lcd.write(tone_data[i]);
    }
}