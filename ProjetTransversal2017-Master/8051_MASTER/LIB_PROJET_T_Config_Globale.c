#ifndef __LIB_BSE_Config_Globale__
#define __LIB_BSE_Config_Globale__
/*---------------------------------------------------------------------------
;
;
;
;
; 	FILE NAME  	: LIB_BSE_Config_Globale
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

#include "LIB_PROJET_T_Config_Globale.h"
#include "LIB_PROJET_T_GPIO.h"  
#include "LIB_PROJET_T_INT_Ext.h"  
#include "LIB_PROJET_T_Timers.h"

#include "LIB_PROJET_T_Clock.h" 
#include "LIB_PROJET_T_ADC.h" 
//------------------------------------------------------------------------------

//*****************************************************************************	 
//Init_Device
//
//	 Cette fonction a pour but de regrouper les fonctions de configurations.
// 
//*****************************************************************************
void Init_Device(void)
{
	EA=0;
	WDTCN     = 0xDE;
	WDTCN     = 0xAD;
	CFG_Clock();
	CFG_GPIO();

	CFG_INT_Ext();

	CFG_Timers();

	CFG_ADC();
}
#endif