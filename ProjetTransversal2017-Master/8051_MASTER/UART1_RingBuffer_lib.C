//---------------------------------------------------------------------------------------
// ID_1.1    UART1_RingBuffer_lib.C -----------------------------------------------------
//---------------------------------------------------------------------------------------
// ID_1.2  Source originale des codes de buffer circulaire: 
//         Microcontroller Programming III	MP7-46 - 
//         Universit� d'Adelaide 
//
// ID_1.3 Adapt� par F.JOLY - CPE Lyon
// ID_1.4 DATE: 08 Mars 2016 
// ID_1.5 Version 1.0 
// 
// ID_1.6 Objectifs ---------------------------------------------------------------------
// Gestion d'une UART en �mission-r�ception par interruption et buffer circulaire
// 
// ID_1.7 D�pendances mat�rielles "cible" ----------------------------------------------- 
// Processeur cible: C8051F02x
// P�riph�rique UART1

// ID_1.8 D�pendances mat�rielles "ext�rieures" -----------------------------------------
// 

// ID_1.9 D�pendances de type communications/protocolaires ------------------------------
// La configuration de la communication UART est du type asynchrone - 8bits - 1 stop bit
// Pas de parit�
//
// ID_1.10 Fonctionnement du code -------------------------------------------------------
// Le code contient:
// - les fonctions de configuration de l'UART1 et de son timer associ�. 
// - Une fonction de cr�ation du buffer circulaire (initialisation de structures)
// - Les fonctions de remplissage du buffer de transmission et les fonctions de vidage 
//   du buffer de r�ception.
//  - La fonction d'interruption UART0 charg�e d'�mettre sur la liaison s�rie le contenu 
//    du buffer de transmission et de stocker dans le buffer de r�ception les donn�es 
//    re�ues sur la liaison s�rie.

// ID_1.11 Choix technologiques divers --------------------------------------------------
// Utilisation de L'UART1 et du Timer 1 comme source d'horloge de l'UART1.
// Pour fonctionner ce code a besoin des macros Define SYSCLK et BAUDRATE

// ID_1.12 Tests r�alis�s ---------------------------------------------------------------
// Validation sur plateforme 8051F020TB avec processeur 8051F020
// Vitesse de transmission: 115200 Baud
// Fr�quence quartz: 22,1184 MHz
//
// ID_1.13 Chaine de compilation --------------------------------------------------------
// KEIL C51 6.03 / KEIL EVAL C51
//
// ID_1.14 Documentation de r�f�rence ---------------------------------------------------
// Datasheet 8051F020/1/2/3  Preliminary Rev. 1.4 12/03 
//
//ID_1.15 Commentaires sur les variables globales et les constantes ---------------------
// La taille des buffers de r�ception et de transmission est modifiable avec la 
// macro MAX_BUFLEN  

//*************************************************************************************************
#include "UART1_RingBuffer_lib.h"



//*************************************************************************************************
// Param�tresd modifiables
//*************************************************************************************************
#define       MAX_BUFLEN 32 // Taille des buffers de donn�es

//*************************************************************************************************
// DEFINITION DES MACROS DE GESTION DE BUFFER CIRCULAIRE
//*************************************************************************************************

// Structure de gestion de buffer circulaire
	//rb_start: pointeur sur l'adresse de d�but du buffer 
	// rb_end: pointeur sur l'adresse de fin du buffer	
	// rb_in: pointeur sur la donn�e � lire
	// rb_out: pointeur sur la case � �crire
		
#define RB_CREATE(rb, type) \
   struct { \
     type *rb_start; \	   
     type *rb_end; \	   
     type *rb_in; \
	   type *rb_out; \		
	  } rb

//Initialisation de la structure de pointeurs 
// rb: adresse de la structure
// start: adresse du premier �l�ment du buffer 
// number: nombre d'�l�ments du buffer - 1	(le "-1" n'est � mon avis pas n�cessaire)
#define RB_INIT(rb, start, number) \
         ( (rb)->rb_in = (rb)->rb_out= (rb)->rb_start= start, \
           (rb)->rb_end = &(rb)->rb_start[number] )

//Cette macro rend le buffer circulaire. Quand on atteint la fin, on retourne au d�but
#define RB_SLOT(rb, slot) \
         ( (slot)==(rb)->rb_end? (rb)->rb_start: (slot) )

// Test: Buffer vide? 
#define RB_EMPTY(rb) ( (rb)->rb_in==(rb)->rb_out )

// Test: Buffer plein?
#define RB_FULL(rb)  ( RB_SLOT(rb, (rb)->rb_in+1)==(rb)->rb_out )

// Incrementation du pointeur dur la case � �crire
#define RB_PUSHADVANCE(rb) ( (rb)->rb_in= RB_SLOT((rb), (rb)->rb_in+1) )

// Incr�mentation du pointeur sur la case � lire
#define RB_POPADVANCE(rb)  ( (rb)->rb_out= RB_SLOT((rb), (rb)->rb_out+1) )

// Pointeur pour stocker une valeur dans le buffer
#define RB_PUSHSLOT(rb) ( (rb)->rb_in )

// pointeur pour lire une valeur dans le buffer
#define RB_POPSLOT(rb)  ( (rb)->rb_out )


//*************************************************************************************************


/* Transmission and Reception Data Buffers */
static char  xdata outbuf[MAX_BUFLEN];     /* memory for transmission ring buffer #1 (TXD) */
static char  xdata inbuf [MAX_BUFLEN];     /* memory for reception ring buffer #2 (RXD) */
static  bit   TXactive = 0;             /* transmission status flag (off) */

/* define out (transmission)  and in (reception)  ring buffer control structures */
static RB_CREATE(out,unsigned char xdata);            /* static struct { ... } out; */
static RB_CREATE(in, unsigned char xdata);            /* static struct { ... } in; */

//**************************************************************************************************
//**************************************************************************************************
void UART1_ISR(void) interrupt 20 {
 
//	static unsigned int cp_tx = 0;
//  static unsigned int cp_rx = 0;
	
  if ((SCON1 & 0x02) == 0x02) // On peut envoyer une nouvelle donn�e sur la liaison s�rie
  { 
  	if(!RB_EMPTY(&out)) {
       SBUF1 = *RB_POPSLOT(&out);      /* start transmission of next byte */
       RB_POPADVANCE(&out);            /* remove the sent byte from buffer */
//			 cp_tx++;
  	}
  	else TXactive = 0;                 /* TX finished, interface inactive */
	SCON1 &= ~0x02;//Clear TI1
  }
  else // RI0 � 1 - Donc une donn�e a �t� re�ue
  {
		if(!RB_FULL(&in)) {                   // si le buffer est plein, la donn�e re�ue est perdue
     	*RB_PUSHSLOT(&in) = SBUF1;        /* store new data in the buffer */
		  RB_PUSHADVANCE(&in);               /* next write location */
//		  cp_rx++;
	 }
   SCON1 &= ~0x01;//Clear RI1
  }
}
// **************************************************************************************************
// init_Serial_Buffer: Initialisation des structuresde gestion des buffers transmission et reception
// *************************************************************************************************
//**************************************************************************************************
void init_Serial_Buffer_1(void) {

    RB_INIT(&out, outbuf, MAX_BUFLEN-1);           /* set up TX ring buffer */
    RB_INIT(&in, inbuf,MAX_BUFLEN-1);             /* set up RX ring buffer */

}
// **************************************************************************************************
// SerOutchar: envoi d'un caract�re dans le buffer de transmission de la liaison s�rie
// *************************************************************************************************
unsigned char serOutchar_1(char c) {

  if(!RB_FULL(&out))  // si le buffer n'est pas plein, on place l'octet dans le buffer
  {                 
  	*RB_PUSHSLOT(&out) = c;               /* store data in the buffer */
  	RB_PUSHADVANCE(&out);                 /* adjust write position */

  	if(!TXactive) {
		TXactive = 1;                      /* indicate ongoing transmission */
 	  SCON1 |= 0x02;//   Placer le bit TI � 1 pour provoquer le d�clenchement de l'interruption
  	}
	return 0;  // op�ration correctement r�alis�e 
  }
   else return 1; // op�ration �chou�e - Typiquement Buffer plein
}
// ************************************************************************************************
//  serInchar: 	lecture d'un caract�re dans le buffer de r�ception de la liaison s�rie
//  Fonction adapt�e pour la r�ception de codes ASCII - La r�ception de la valeur binaire 0
//  n'est pas possible (conflit avec le code 0 retourn� si il n'y a pas de caract�re re�u)
// ************************************************************************************************
char serInchar_1(void) {
char c;

  if (!RB_EMPTY(&in))
  {                 /* wait for data */

  	c = *RB_POPSLOT(&in);                 /* get character off the buffer */
 	  RB_POPADVANCE(&in);                   /* adjust read position */
  	return c;
  }
  else return -1;
}
// ************************************************************************************************
//  serInchar_Bin: 	lecture d'un caract�re dans le buffer de r�ception de la liaison s�rie
//  Fonction adapt�e pour la r�ception de codes Binaires - Cette fonction retourne un entier. 
//  L'octet de poids faible correspond au caract�re re�u, l'octet de poids fort, s'il est nul indique 
//  qu'aucun caract�re n'a �t� re�u.
//  
// ************************************************************************************************
//unsigned int serInchar_Bin_1(void) {
//char c;
//unsigned int return_code = 0;
//	 
//  if (!RB_EMPTY(&in))
//  {                
//    // un caract�re au moins est dans le buffer de r�ception
//  	c = *RB_POPSLOT(&in);                 /* get character off the buffer */
// 	  RB_POPADVANCE(&in);                   /* adjust read position */
//  	return 0xFF00+c;
//  }
//	// pas de caract�re dans le buffer de r�ception.
//  else return return_code;
//}
// *************************************************************************************************
// serOutstring:  Envoi d'une chaine de caract�re dans le buffer de transmission
// ************************************************************************************************
unsigned char serOutstring_1(char *buf) {
unsigned char len,code_err=0;

  for(len = 0; len < strlen(buf); len++)
     code_err +=serOutchar_1(buf[len]);
  return code_err;
}
//*************************************************************************************************
//  CONFIGURATION BAS NIVEAU de L'UART1
//*************************************************************************************************

//*****************************************************************************
#define Preload_Timer0 (SYSCLK/(BAUDRATE*16))
#if Preload_Timer0 > 255 
#error "Valeur Preload Timer0 HORS SPECIFICATIONS"
#endif 

 
//*****************************************************************************	 
//CFG_uart1_mode1 et uart0
//
//*****************************************************************************	 
void cfg_UARTS_mode1(void)
{
		T4CON = 0xCF;     // Source clock Timer 1 pour uart1
		RCLK0 = 0;     // Source clock Timer 1 pour uart0
		TCLK0 = 0;
	
		PCON  |= 0x90;
		PCON &= 0xB7;  // SSTAT0=0	et SSTAT1=0 SMOD0 = 0 = SMOD1

	  SCON0 = 0x70;   // Mode 1 - Check Stop bit - Reception valid�e
		SCON1 = 0x52;//Mode 1 8 bit RX actif TI1 actif interruption ok

		TI0 = 1;        // Transmission: octet transmis (pr�t � recevoir un char
					          // pour transmettre					
    ES0 = 1;        // interruption UART0 autoris�e	
		EIE2 |= 0x40; //Active interruption UART1
	
	
}


