/*---------------------------------------------------------------------------
;
;
;
;
; 	FILE NAME  	: LIB_BSE_Clock
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
#include "LIB_PROJET_T_Clock.h"

//*****************************************************************************	 
//CFG_Clock
//
//	 Cette fonction a pour but de regrouper les fonctions de configurations de l'horloge systeme.
// 
//*****************************************************************************
void CFG_Clock(void)
{
	OSCXCN=0x67;
	while(((OSCXCN&0x80)>>7)!=1);//Waiting for crystal oscillator is running and stable
	OSCICN|=0x08;
	OSCICN&=~(0x06);
}
