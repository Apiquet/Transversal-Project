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

#ifndef __LIB_PROJET_T_Timers__
#define __LIB_PROJET_T_Timers__
//*****************************************************************************	 
//CFG_Timers
//
//	 Cette fonction a pour but de regrouper les fonctions de configurations des Timers.
// 
//*****************************************************************************

void CFG_Timers(void);
void Config_Timer3(void);
void Config_Timer2(void);
void Config_Timer1(void);

unsigned long int Conversion_horloge_en_centiemes();
void Horloge_RTC(void);
void clear_RTC(void);
#endif