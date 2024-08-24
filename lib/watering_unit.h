#ifndef WATERING_UNIT_H
# define WATERING_UNIT_H

# define INPUT_PIN 33
# define PUMP_PIN 32
# define THRESHOLD_MOISTURE 40.0

# include <HTTPClient.h>
# include <M5Unified.h>

void	initializeSystem(void);
void	measureAndDisplayMoisture(float &vol, float &moisture);
void	controlPump(float moisture, int &number);
void	displayGraph(float moisture, float moistureHistory[],
			int &currentIndex);
void	handleEffects(float moisture, int number);
void	sendToCloud(float vol, float moisture);
void	notifyLine(float vol, float moisture);

#endif