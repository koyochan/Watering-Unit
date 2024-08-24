#include "../lib/watering_unit.h"

void	initializeSystem(void)
{
	M5.begin();
	Serial.begin(115200);
	pinMode(INPUT_PIN, INPUT);
	pinMode(PUMP_PIN, OUTPUT);
	M5.Lcd.setRotation(1);
	M5.Lcd.setTextFont(2);
	M5.Lcd.setBrightness(255);
}