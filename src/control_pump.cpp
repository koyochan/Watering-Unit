#include "../lib/enable.h"
#include "../lib/watering_unit.h"
#include "../lib/image.h"
#include "../lib/tone_data.h"

void controlPump(float moisture, int &number) {
    static bool pumpOn = false;

    if (moisture <= THRESHOLD_MOISTURE) {
        if (!pumpOn) {
            number++;
            pumpOn = true;
            digitalWrite(PUMP_PIN, HIGH);
            Serial.println("ポンプオン");
            M5.Lcd.fillScreen(RED);
            M5.Lcd.setTextColor(WHITE, RED);
            M5.Lcd.drawString("Pump On", 40, 50);
            
            #if ENABLE_SOUND_ALERT
                playTone();
            #endif
            
            #if ENABLE_VISUAL_EFFECT
                drawImage(40, 70, image_data, 135, 240);  // 135 x 240 Pixel (M5StickCPlus2)
            #endif
        }
    } else {
        if (pumpOn) {
            pumpOn = false;
            digitalWrite(PUMP_PIN, LOW);
            Serial.println("ポンプオフ");
            M5.Lcd.fillScreen(BLACK);
            M5.Lcd.setTextColor(WHITE, BLACK);
            M5.Lcd.drawString("Pump Off", 40, 50);
        }
    }
}
