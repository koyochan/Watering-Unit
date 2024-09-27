#include "../lib/enable.h"
#include "../lib/watering_unit.h"

float vol, moisture;
int		number = 0;
float	moistureHistory[320];
int		currentIndex = 0;

void	setup(void)
{
	initializeSystem();
}

void	loop(void)
{
	M5.update();
	measureAndDisplayMoisture(vol, moisture);
	controlPump(moisture, number);
	#if ENABLE_GRAPH_DISPLAY
		void displayGraph(float moisture, float moistureHistory[],
			int currentIndex);
	#endif
	#if ENABLE_LINE_NOTIFY
		void notifyLine(float vol, float moisture);
	#endif
}
