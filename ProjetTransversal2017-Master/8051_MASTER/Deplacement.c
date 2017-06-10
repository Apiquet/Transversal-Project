#include "Deplacement.h"
#include "Communication.h"
#include "Global.h"
#include <UART0_RingBuffer_lib.h>
#include <UART1_RingBuffer_lib.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#define M_PI 3.14159265358979323846
extern char Busy_UART1;
extern int Vitesse_Robot;//pourcentage 	
extern int X_POS,Y_POS,A_POS,X_DEST,Y_DEST,A_DEST,A_FIN;
extern char Mooving;
extern char Params_Change;
extern char Deplacement_Demande;
extern int distance_avant ;
extern int distance_avant_IR ; 
void DeplacementContinu(int speed)
{
			char Envoi[40];
	sprintf(Envoi,"mogo 1:%d 2:%d \r",speed,speed);
		serOutstring_1(Envoi);
	#if SERIAL0SPY
		serOutstring(Envoi);
	#endif
	Busy_UART1=1;
}

void DeplacementDistance(int distance,int speed)
{
				char Envoi[40];
				sprintf(Envoi,"digo 1:%d:%d 2:%d:%d \r",distance*COEFF_CM_TO_TICK,speed,distance*COEFF_CM_TO_TICK,speed);
				serOutstring_1(Envoi);

	#if SERIAL0SPY
		serOutstring(Envoi);
	#endif
	Busy_UART1=1;
}

void Tourner(int angle,int speed)
{
	
	char Envoi[40];
				sprintf(Envoi,"digo 1:%0.0f:%d 2:%0.0f:%d \r",-angle*5.40,speed,angle*5.40,speed);
				serOutstring_1(Envoi);

	#if SERIAL0SPY
		serOutstring(Envoi);
	#endif
	Busy_UART1=1;
}

int Analyse_Deplacement()
 {
 	if(Busy_UART1==1)//Si le robot est occupé on analyse pas les prochaines demandes
 	{
 		return 0;
 //		serOutstring("Nothing\n");
 	}
	if(Mooving==1)
	{//Le robot se deplacait on cherche a savoir si il se deplace toujours
		Check_Arrivee();
		return 0;
	}
 	//Le robot n'est pas occupé, il doit donc se deplacer
 	if(X_POS!=X_DEST || Y_POS!=Y_DEST )
 	{//Mauvaise position XY, on calcule donc O optimal et on s'y place
 		A_DEST=atan2(Y_POS-Y_DEST,X_DEST-X_POS)* 180 / M_PI +90;
		
 	}
 	else
 	{//Position XY bonne, on se met donc a l'angle voulu
 		A_DEST=A_FIN;
 	}
 		if(A_POS!=A_DEST)
 		{//On se met a l'angle voulu si on ne l'est pas
			int erreur=-(A_POS-A_DEST);
			 Tourner(erreur,Vitesse_Robot);
			Params_Change=1;//1 Pour Angle a modifier
			Mooving=1;
 			return 1;
 		}
 		else
 		{//Si on est a l'angle voulu on se déplace
 			int dx=X_DEST-X_POS;
 			int dy=Y_DEST-Y_POS;
 			int Distance = sqrt(dx*dx+dy*dy);
			if(distance_avant<Distance)
				return 0;
 			if(Distance==0)
 			{//Rien a deplacer;
				Params_Change=-1;//-1 Pour rien
				if(Deplacement_Demande==1)
				{
					serOutstring("\r\nB");
					X_POS=0;
					Y_POS=0;
					A_DEST=0;
					A_POS=0;
					X_DEST=0;
					Y_DEST=0;
					Ready_To_Continue();

				Deplacement_Demande=0;
				}
 				return 0;
 			}
 			DeplacementDistance(Distance,Vitesse_Robot);
			Params_Change=2;//2 Pour distance
			Mooving=1;

 			Busy_UART1=1;
 			return 1;
 		}
 }
 void Check_Arrivee()
 {
	 serOutstring_1("pids \r");
	 Busy_UART1=1;
 }