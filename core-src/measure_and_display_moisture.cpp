#include "../lib/watering_unit.h"

void	measureAndDisplayMoisture(float &vol, float &moisture)
{
	float	adc;

	adc = analogRead(INPUT_PIN);
	vol = (adc + 1) * 3.3 / (4095 + 1);
	moisture = 100 * (1.65 - vol) / (1.65 - 1.2);
	Serial.printf("電圧: %2.2fV  土壌水分量: %0.2f%%\r\n", vol, moisture);
	M5.Lcd.setCursor(0, 0);
	M5.Lcd.setTextColor(WHITE);
	M5.Lcd.printf("Voltage: %2.2fV\n", vol);
	M5.Lcd.printf("Moisture: %0.2f%%\n", moisture);
	delay(1000);
}
