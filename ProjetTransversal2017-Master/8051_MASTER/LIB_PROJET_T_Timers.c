/*---------------------------------------------------------------------------
;
;
;
;
; 	FILE NAME  	: LIB_BSE_Timers
; 	TARGET MCUs	: C8051F020, 
; 	DESCRIPTION	: Fonctions Bas niveau pour le TP EMBARQUE
;
; 	REVISION 1.0
;
;---------------------------------------------------------------------------*/
//-------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------------
#include <c8051f020.h>                    // SFR declarations
#include "LIB_PROJET_T_Timers.h"

unsigned char RTC_Centieme=0;
unsigned char RTC_Secondes=0;
unsigned char RTC_Minutes=0;
unsigned char RTC_Heures=0;
//*****************************************************************************	 
//CFG_Global
//
//	 Cette fonction a pour but de regrouper les fonctions de configurations des Timers.
// 
//*****************************************************************************

void CFG_Timers(void)
{
Config_Timer2();
Config_Timer3();
}
void Config_Timer2(void)
{
	T2CON = 0x00;   // Reset du timer2
	
	CKCON&=0xDF;//Divide system clock by 12
	
	TF2=0;
	EXF2=0;
	EXEN2=0;
	CT2=0;
	RCLK0=0;
	TCLK0=0;
	CPRL2=0;
	
   RCAP2H = 0xFF;   //On défini la valeur de reload du timer
	 RCAP2L = 0x46; // pour avoir 0.1 ms de periode
	
   TL2 = 0xFF;  // On remplit le timer
   TH2 = 0xFF;
	
	TR2=1;
	PT2=1;
	ET2=1;
		
 // IE   |= 0x20;   // On autorise les interruptions généré par le timer 2
	 //PT2 = 1;
   //T2CON |= 0x04; // On lance le timer
}
void Config_Timer3(void)
{
	TMR3CN |=0x04;
	TMR3RLH =0xFF;
		TMR3RLL =0x46;
	TMR3L=0xFF;
	TMR3H=0xFF;
	EIE2|=0x01;
}