#include <M5Unified.h>

#define INPUT_PIN 33
#define PUMP_PIN 32
#define THRESHOLD_MOISTURE 40.0

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
}

void	loop(void)
{
	static bool	pumpOn = false;
	float		adc;
	int			flag;

	flag = 0;
	M5.update();
	adc = analogRead(INPUT_PIN);
	vol = (adc + 1) * 3.3 / (4095 + 1);
	moisture = 100 * (1.65 - vol) / (1.65 - 1.2);
	Serial.printf("電圧: %2.2fV  土壌水分量: %0.2f%%\r\n", vol, moisture);
	if (moisture <= THRESHOLD_MOISTURE)
	{
		if (!pumpOn)
		{
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
	M5.Lcd.setCursor(0, 0);
	M5.Lcd.setTextColor(WHITE, BLACK);
	M5.Lcd.printf("Voltage: %2.2fV\n", vol);
	M5.Lcd.printf("Moisture: %0.2f%%\n", moisture);
	M5.Lcd.printf("Number of waterings: %2.2fV\n", vol);
	delay(1000);
}
