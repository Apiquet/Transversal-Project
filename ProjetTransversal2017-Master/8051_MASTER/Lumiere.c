#include "Lumiere.h"
#include <c8051f020.h>    
extern char LED_activee;

extern int intensite;
extern long int duree_allumage;
extern long int duree_extinction;
extern int nb_cycles;
int pilotage_led(){
	static int cpt_LED_intensite = 0;
 static long int cpt_LED_allumage = 0;
 static long int cpt_LED_extinction = 0;
 static long int cpt_LED_temps = 0;
 static int cpt_LED_cycles = 0;
  
  if(cpt_LED_cycles<nb_cycles)
  {
    if(cpt_LED_allumage<=duree_allumage*1000)
    {
      if(cpt_LED_intensite >= 100) // si on arrive a 10ms
      {
       cpt_LED_intensite = 0;
      }
      else if(cpt_LED_intensite <= intensite) // etat haut de la pulse
      {
        P3 |= 0x80; // etat haut pour P3.7 (LED)
      }
      else // etat bas, reste de la periode
      {
        P3 &= 0x7F; // eteind P3.7 le reste de la pulse

      }
      cpt_LED_intensite++;;
      cpt_LED_allumage++;
      cpt_LED_temps++;
    }
    else if(cpt_LED_extinction<=duree_extinction*1000)
    {
      P3 &= 0x7F; // eteind P3.7 pendant la durée d'extinction
      cpt_LED_extinction++;
      cpt_LED_temps++;
    }
               
                if(cpt_LED_temps>=(duree_allumage+duree_extinction)*1000){
                    cpt_LED_cycles++;
                    cpt_LED_temps=0;
          cpt_LED_allumage=0;
          cpt_LED_extinction=0;
                }

   }else{
     cpt_LED_temps=0;
     cpt_LED_allumage=0;
     cpt_LED_extinction=0;
     cpt_LED_cycles=0;
     nb_cycles=0;
		 P3 &= 0x7F; // eteind P3.7 le reste de la pulse

     //LED_activee=0;
     return 1; //les cycles sont finis
   }
   return 0; //cycles non finis
			
}