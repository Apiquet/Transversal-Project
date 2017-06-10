#include "ServoMoteur.h"
#include "Global.h"
#include "LIB_PROJET_T_ADC.h" 
#include "Lumiere.h" 
#include <UART0_RingBuffer_lib.h>
#include <stdio.h>
 
extern int pulse_servo_H,pulse_servo_V;
extern int angle;
extern int distance_avant, distance_arriere;
extern int compteur_telemetre, compteur_telemetre_arriere;
extern unsigned long int Time_in_ms;

extern int distances_telemetre[36];
extern int launch_detection;
extern int mode_detection;
extern int pas_angle_detection;

void ISR_Timer2(void) interrupt 5 // interrupt toutes les 0.1ms
{

	TF2 = 0;
	
	//////////////////////////////////////////
	// Telemetre ultrason   --> Crée une pulse sur P6.4 et l'echo est renvoyé sur INT1 
	//////////////////////////////////////////
	if(compteur_telemetre ==0 )
	{
			P6 |= 0x10; // P6.4   à l'état haut pour 100us(pulse) pour declencher trig telemetre ultrason
	}
	else
	{
		P6 &= 0xEF; // P6.4 retourne à etat bas le reste du temps 
		
	}
	
	if(compteur_telemetre_arriere ==0 )
	{
			P6 |= 0x20; // et P6.5 à l'état haut pour 100us(pulse) pour declencher trig telemetre ultrason
	}
	else
	{
			P6 &= 0xDF; //  et P6.5 retourne à etat bas le reste du temps 
		
	}
		compteur_telemetre++;//on compte
		compteur_telemetre_arriere++;

}

void ISR_Timer3(void) interrupt 14 // interrupt toutes les 0.1ms
{

	static int cpt_servo_H = 0; 
	static int cpt_servo_V = 0; 
	static int cmpt_time=0;

	TMR3CN &= 0x7F; //TF3 remet flag a 0
	
	cmpt_time++;
	if(cmpt_time==10)
	{
		Time_in_ms++;
		cmpt_time=0;
	}
	//////////////////////////////////////////
	// Servomoteur Horizontal   --> Crée une pulse de periode 20ms avec etat haut entre 0.5 et 2.8ms (lié à l'angle voulue)
	//////////////////////////////////////////
	if(cpt_servo_H > 200) // si on arrive a 20ms
	{
		cpt_servo_H = 0;
	}
	else if(cpt_servo_H <= pulse_servo_H) // etat haut de la pulse
	{
			P3 |= 0x40; // etat haut pour P3.6 qui represente le servo horizontal
	}
	else // etat bas, reste de la periode
	{
			P3 &= 0xBF; // eteind P3.6 le reste de la pulse
	}
	cpt_servo_H = cpt_servo_H + 1;
	
	//////////////////////////////////////////
	// Servomoteur Vertical   --> Crée une pulse de periode 20ms avec etat haut entre 0.5 et 2.8ms (lié à l'angle voulue)
	//////////////////////////////////////////
	if(cpt_servo_V > 200) // si on arrive a 20ms
	{
		cpt_servo_V = 0;
	}
	else if(cpt_servo_V <= pulse_servo_V) // etat haut de la pulse
	{
			P3 |= 0x10; // etat haut pour P3.6 qui represente le servo horizontal
	}
	else // etat bas, reste de la periode
	{
			P3 &= 0xEF; // eteind P3.6 le reste de la pulse
	}
	cpt_servo_V = cpt_servo_V + 1;
	
	
		//////////////////////////////////////////
	//Pilotage led en temps et en intensité en fonction de l'épreuve
	//////////////////////////////////////////
    pilotage_led();
	//P3&=0xEF;
	
}

void reception_telemetre_ultrason(void) interrupt 2//P2.5 ECHO
{

	distance_avant= 340*compteur_telemetre/(200) - 7; //calcul distance entre l'obstacle et le robot:
	//onde à 340m/s, compteur incrémenté toutes les 0.1ms 
	// On multiplie 340 par 100 pour avoir cm/s // On divise par 10000 compteur telemetre pour avoir en secondes et on divise par 2 (aller retour ECHO)
	//if(distance_avant>25)
		//distance_avant=ACQ_ADC();//Mesure de l'infrarouge , ainsi temps d'acquisition identique
	
		compteur_telemetre=-DELAY_ULTRASON; // reinitialisation compteur temps pulse-echo
			
	
	
	IE1=0; // remets flag a 0*/
}

void reception_telemetre_ultrason_arriere(void) interrupt 0
{
	distance_arriere= 340*compteur_telemetre_arriere/(200) - 7; //calcul distance entre l'obstacle et le robot:
	//onde à 340m/s, compteur incrémenté toutes les 0.1ms 
	// On multiplie 340 par 100 pour avoir cm/s // On divise par 10000 compteur telemetre pour avoir en secondes et on divise par 2 (aller retour ECHO)
	//if(distance_arriere>25)
				//distance_arriere=ACQ_ADC_2();//Mesure de l'infrarouge , ainsi temps d'acquisition identique

		compteur_telemetre_arriere=-DELAY_ULTRASON; // reinitialisation compteur temps pulse-echo
	
	

	IE0=0; // remets flag a 0*/
}



//////////////////////////////////////////
// Fonction permettant de fixer l'angle du servo horizontal
//////////////////////////////////////////
void Gen_Servo_Horizontal(int angle)
{
	if( (angle <= 90) && (angle >= -90) )
	{
		pulse_servo_H = (-11*angle+1500)/100; // definit le nombre d'overflow  de 0.1ms timer2 (durée pulse) correspondant à l'angle
		// -90° = 0.9ms / 0° = 1.5ms / 90° = 2.1ms //
		// Equation regi par le systeme : tpulse = 15 + angle*0.07 et on multiplie le tout par 1000 afin d'eviter les arrondis puis on redivise par 1000
	}

	
}


//////////////////////////////////////////
// Fonction permettant de fixer l'angle du servo vertical
//////////////////////////////////////////
void Gen_Servo_Vertical(int angle)
{
	if( (angle <= 90) && (angle >= -90) )
	{
		pulse_servo_V = (11*angle+1500)/100; // definit le nombre d'overflow  de 0.1ms timer2 (durée pulse) correspondant à l'angle
		// -90° = 0.9ms / 0° = 1.5ms / 90° = 2.1ms //
		// Equation regi par le systeme : tpulse = 15 + angle*0.07 et on multiplie le tout par 1000 afin d'eviter les arrondis puis on redivise par 1000
		
	}

}	

void detection_obstacles(int mode, int pas_angle)
{
	static int angle_servo = -90;
	static unsigned long  int Time_Past_detection = 0;
	int n	= 360/pas_angle;
	static int iterateur_telemetre = 0;
	

	if( (launch_detection == 1) && (angle_servo <= 90) )
	{
				Gen_Servo_Horizontal(angle_servo);
				
				if(Time_in_ms > (Time_Past_detection + 1500) )
				{
					distances_telemetre[iterateur_telemetre] = distance_avant;
					angle_servo+=pas_angle;
					Time_Past_detection = Time_in_ms;
					
					if(mode == 2) // detection a 360°
					{
							distances_telemetre[iterateur_telemetre+n/2] = distance_arriere;
					}
					
					iterateur_telemetre++;
					
				}	

					serOutstring("D\r");

	}
	else if(angle_servo > 90)
	{

		char Envoi[200]="";
		int i=0;
			angle_servo = -90;
		  iterateur_telemetre = 0;
		  launch_detection = 0;
		for( i=0;i<n;i++)
		{
					sprintf(Envoi,"%s %d:%d",Envoi,-90+i*pas_angle,distances_telemetre[i]);
		}
							sprintf(Envoi,"%s \r",Envoi);
		serOutstring(Envoi);
		  // envoyer message de tout le tableau
		  // clean tableau 
		  // clean_distance tableau;
	}

	
}