

// グラフ表示機能
void	displayGraph(float moisture, float moistureHistory[], int &currentIndex)
{
	int	x1;
	int	y1;
	int	x2;
	int	y2;

	moistureHistory[currentIndex] = moisture;
	currentIndex = (currentIndex + 1) % 320;
	M5.Lcd.fillScreen(TFT_BLACK);
	for (int i = 0; i < 319; i++)
	{
		x1 = i;
		y1 = 240 - moistureHistory[(currentIndex + i) % 320] * 2;
		x2 = i + 1;
		y2 = 240 - moistureHistory[(currentIndex + i + 1) % 320] * 2;
		uint16_t color = M5.Lcd.color565(random(0, 255), random(0, 255),
				random(0, 255)); // ランダムカラー
		M5.Lcd.drawLine(x1, y1, x2, y2, color);
	}
}

// エフェクト機能

void	handleEffects(float moisture, int number)
{
	static bool	pumpOn = false;

	if (moisture <= THRESHOLD_MOISTURE && !pumpOn)
	{
		pumpOn = true;
		digitalWrite(PUMP_PIN, HIGH);
		Serial.println("ポンプオン");
		M5.Lcd.fillScreen(RED);
		M5.Lcd.setTextColor(WHITE, RED);
		M5.Lcd.drawString("Pump On", 40, 50);
		displayGIF("pump_on.gif");
		M5.Speaker.tone(440, 500); // 音を鳴らす
	}
	else if (moisture > THRESHOLD_MOISTURE && pumpOn)
	{
		pumpOn = false;
		digitalWrite(PUMP_PIN, LOW);
		Serial.println("ポンプオフ");
		M5.Lcd.fillScreen(BLACK);
		M5.Lcd.setTextColor(WHITE, BLACK);
		M5.Lcd.drawString("Pump Off", 40, 50);
	}
}

// Wi-Fi接続、クラウド送信、LINE通知機能
void	sendToCloud(float vol, float moisture)
{
	HTTPClient	http;
	String		httpRequestData;
	int			httpResponseCode;
	String		response;

	if (WiFi.status() == WL_CONNECTED)
	{
		http.begin(serverName);
		http.addHeader("Content-Type", "application/x-www-form-urlencoded");
		httpRequestData = "voltage=" + String(vol) + "&moisture="
			+ String(moisture);
		httpResponseCode = http.POST(httpRequestData);
		if (httpResponseCode > 0)
		{
			response = http.getString();
			Serial.println(response);
		}
		http.end();
	}
}

void	notifyLine(float vol, float moisture)
{
	HTTPClient	http;
	String		message;
	String		httpRequestData;
	int			httpResponseCode;
	String		response;

	if (WiFi.status() == WL_CONNECTED)
	{
		http.begin("https://notify-api.line.me/api/notify");
		http.addHeader("Authorization", "Bearer " + String(lineToken));
		http.addHeader("Content-Type", "application/x-www-form-urlencoded");
		message = "Voltage: " + String(vol) + "V\nMoisture: " + String(moisture)
			+ "%";
		httpRequestData = "message=" + message;
		httpResponseCode = http.POST(httpRequestData);
		if (httpResponseCode > 0)
		{
			response = http.getString();
			Serial.println(response);
		}
		http.end();
	}
}

// GIF表示関数
void	displayGIF(const char *gifName)
{
	// GIFを表示するためのコードをここに実装
}