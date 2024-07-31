#include <M5Unified.h>

#define INPUT_PIN 33
#define PUMP_PIN 32

float vol, moisture;

void	setup(void)
{
	M5.begin();
	Serial.begin(115200);
	pinMode(INPUT_PIN, INPUT);
	pinMode(PUMP_PIN, OUTPUT);
	M5.Lcd.setRotation(1);
	M5.Lcd.setTextFont(2);
	M5.Lcd.setBrightness(255);
	disableCore0WDT();
	disableCore1WDT();
}

void	loop(void)
{
	static bool	pumpOn = false;
	float		adc;

	M5.update();
	if (M5.BtnB.wasPressed())
	{
		pumpOn = !pumpOn;
		digitalWrite(PUMP_PIN, pumpOn ? HIGH : LOW);
		if (pumpOn)
		{
			Serial.println("Pump ON");
			M5.Lcd.fillScreen(RED);
			M5.Lcd.setTextColor(WHITE, RED);
			M5.Lcd.drawString("Pump ON", 40, 50);
		}
		else
		{
			Serial.println("Pump OFF");
			M5.Lcd.fillScreen(BLACK);
			M5.Lcd.setTextColor(WHITE, BLACK);
			M5.Lcd.drawString("Pump OFF", 40, 50);
		}
	}
	adc = analogRead(INPUT_PIN);
	vol = (adc + 1) * 3.3 / (4095 + 1);
	moisture = 100 * (1.65 - vol) / (1.65 - 1.2);
	Serial.printf("Voltage: %2.2fV  Moisture: %0.2f%%\r\n", vol, moisture);
	M5.Lcd.setCursor(0, 0);
	M5.Lcd.setTextColor(WHITE, BLACK);
	M5.Lcd.printf("Voltage: %2.2fV\n", vol);
	M5.Lcd.printf("Moisture: %0.2f%%\n", moisture);
	delay(1000);
}
