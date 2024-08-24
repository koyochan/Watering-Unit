#include "../lib/enable.h"
#include "../lib/watering_unit.h"
#include "../lib/image.h"
#include "../lib/tone_data.h"

void drawImage(int x, int y, const unsigned char *image, int width, int height) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            uint16_t color = pgm_read_word(&(image[i * width + j]));
            M5.Lcd.drawPixel(x + j, y + i, color);
        }
    }
}

void playTone() {
    for (int i = 0; i < sizeof(tone_data) / sizeof(tone_data[0]); i++) {
        M5.Lcd.write(tone_data[i]);
    }
}

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
