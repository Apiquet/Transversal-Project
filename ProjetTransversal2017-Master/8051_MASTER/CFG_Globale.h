#ifndef CONFIG_GLOBALE_H
#define CONFIG_GLOBALE_H
#include <c8051f020.h>
#include <stdio.h>
#include <intrins.h>
#include <string.h>
/*---------------------------------------------------------------------------
;
;

;
;---------------------------------------------------------------------------*/
#define SYSCLK 22118400 //approximate SYSCLK frequency in Hz
#define BAUDRATE  19200L          // Baud rate of UART in bps
																 // Le caractère 'L' force l'évaluation de BAUDRATE en entier long
//#define TICK_CLK  200  // (en hertz)
#endif
																											// 
