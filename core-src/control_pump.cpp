#include "../lib/watering_unit.h"

void	controlPump(float moisture, int &number)
{
	static bool pumpOn = false;

	if (moisture <= THRESHOLD_MOISTURE)
	{
		if (!pumpOn)
		{
			number++;
			pumpOn = true;
			digitalWrite(PUMP_PIN, HIGH);
			Serial.println("ポンプオン");
			M5.Lcd.fillScreen(RED);
			M5.Lcd.setTextColor(WHITE, RED);
			M5.Lcd.drawString("Pump On", 40, 50);
		}
	}
	else
	{
		if (pumpOn)
		{
			pumpOn = false;
			digitalWrite(PUMP_PIN, LOW);
			Serial.println("ポンプオフ");
			M5.Lcd.fillScreen(BLACK);
			M5.Lcd.setTextColor(WHITE, BLACK);
			M5.Lcd.drawString("Pump Off", 40, 50);
		}
	}
}