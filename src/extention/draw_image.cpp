#include "../../lib/watering_unit.h"

void drawImage(int x, int y, const unsigned char *image, int width, int height) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            uint16_t color = pgm_read_word(&(image[i * width + j]));
            M5.Lcd.drawPixel(x + j, y + i, color);
        }
    }
}