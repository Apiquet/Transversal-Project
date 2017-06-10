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
//-------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------------
#include "LIB_PROJET_T_ADC.h" 
#include <stdio.h>
#include <UART0_RingBuffer_lib.h>
#include <UART1_RingBuffer_lib.h>

//////////////////////////////////////////
// Configuration ADC0 pour télémetre infrarouge
//////////////////////////////////////////
void CFG_ADC(void)
{
	CFG_VREF();
  CFG_ADC0();
}
void CFG_VREF(void)
{
	REF0CN|=0x03; //Activation tension de reference sur le port VREF
}

void CFG_ADC0(void)
{
	AMX0CF&=0xF8; 
	AMX0SL=0x03; 	//On utilise le port AIN0.3,Utilisation AIN0.3 en unipolaire
	ADC0CN&=0x8f; //Conversion declenchée par une mise a 1 de AD0BUSY
	AD0TM=0; 			//Conversion declenchée par une mise a 1 de AD0BUSY
	AD0LJST=1;
	AD0EN=1; 			//Activation ADC0
	AD0INT=0; 		//ADC0 pret
	ADC0CF &=0x0F;
	
}


//////////////////////////////////////////
// Calcul de la distance, retourne la distance en cm
//////////////////////////////////////////
int ACQ_ADC(void)
{
	int Value_ADC=0;
	AMX0SL=0x03; 	//On utilise le port AIN0.3,Utilisation AIN0.3 en unipolaire
	AD0BUSY=1; 				//lancement conversion
 	while(AD0INT!=1) ;//Attente fin de conversion
	Value_ADC=ADC0H;
	AD0INT=0;					//raz le flag
	if(Value_ADC>116) return (380-Value_ADC)/5.44;
	else return (164-Value_ADC)/1.16; //retourne la distance en cm
}

int ACQ_ADC_2(void)
{
	int Value_ADC=0;
	AMX0SL=0x05; 	//On utilise le port AIN0.5,Utilisation AIN0.5 en unipolaire
	AD0BUSY=1; 				//lancement conversion
 	while(AD0INT!=1) ;//Attente fin de conversion
	Value_ADC=ADC0H;
	AD0INT=0;					//raz le flag
	if(Value_ADC>116) return (380-Value_ADC)/5.44;
	else return (164-Value_ADC)/1.16; //retourne la distance en cm
	
	
}