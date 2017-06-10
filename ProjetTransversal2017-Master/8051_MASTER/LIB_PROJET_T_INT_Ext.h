/*---------------------------------------------------------------------------
;
;
;
;
; 	FILE NAME  	: LIB_BSE_INT_Ext
; 	TARGET MCUs	: C8051F020, 
; 	DESCRIPTION	: Fonctions Bas niveau pour le TP EMBARQUE
;
; 	REVISION 1.0
;
;---------------------------------------------------------------------------*/

#ifndef __LIB_PROJET_T_INT_Ext__
#define __LIB_PROJET_T_INT_Ext__


//*****************************************************************************	 
//CFG_INT_Ext
//
//	 Cette fonction a pour but de regrouper les fonctions de configurations des interruptions externes.
// 
//*****************************************************************************

void CFG_INT_Ext(void);
void Enable_interrupt(void);
void Disable_interrupt(void);
void Config_INT1(void);
void Config_INT0(void);
void CLEAR_TF2(void);
void CLEAR_IE1(void);

#endif