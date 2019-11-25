#include <stdlib.h>
#include <wiringPi.h> // -lwiringPi
#include <pcf8591.h> // -lbcm2835

#define Address 0x48 // i2cdetect -y 1 nos da este valor
#define BASE 64
#define A0 BASE+0
#define A1 BASE+1
#define A2 BASE+2
#define A3 BASE+3	// No se usa de momento, es para leer el valor externo

void adcCrudo(int inicializar, int *potenciometro, int *fotocelula, int *thermistor){
	if(inicializar) pcf8591Setup(BASE,Address);

	*potenciometro 	= analogRead(A0);
	*fotocelula 	= analogRead(A1);
	*thermistor 	= analogRead(A2);
}
