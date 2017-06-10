/*---------------------------------------------------------------------------
;
;
;
;
; 	FILE NAME  	: LIB_BSE_ADC
; 	TARGET MCUs	: C8051F020, 
; 	DESCRIPTION	: Fonctions Bas niveau pour le TP EMBARQUE
;
; 	REVISION 1.0
;
;---------------------------------------------------------------------------*/
#ifndef __LIB_PROJET_T_ADC__
#define __LIB_PROJET_T_ADC__
void CFG_ADC(void);
void CFG_VREF(void);
void CFG_ADC0(void);


//////////////////////////////////////////
// Calcul de la distance, retourne la distance en cm
//////////////////////////////////////////
int ACQ_ADC(void);
int ACQ_ADC_2(void);
#endif