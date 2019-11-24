#include <wiringPi.h>



void led_config(int *leds)
{
	
	wiringPiSetup();	// Inicializo las funciones de wiringPi, necesario segun documentacion
	pinMode(leds[0], OUTPUT);	
	pinMode(leds[1], OUTPUT);
	pinMode(leds[2], OUTPUT);
	pinMode(leds[3], OUTPUT);
	pinMode(leds[4], OUTPUT);
	pinMode(leds[5], OUTPUT);
	pinMode(leds[6], OUTPUT);
	pinMode(leds[7], OUTPUT);
}
