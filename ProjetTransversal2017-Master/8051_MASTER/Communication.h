#ifndef __Communication__h
#define __Communication__h


enum Message_Commande {Empty,D, E, Q, TV, A, B_message, S, RD, RG, RC,RA,G,ASS,MI,ME,IPO,POS,MOU,MOB,SD,L,LS,CS,PPH,SPH,AUX};
enum Retour_Serializer {EMPTY,ACK,NACK,TRUE,FALSE};
typedef enum Retour_Serializer Retour_Serializer;
typedef enum Message_Commande Message_Commande;
Message_Commande Parseur_Uart_0(char entree[]);
Retour_Serializer Parseur_Uart_1(char entree[]);
void SerialEvent0();
void SerialEvent1();

void Ready_To_Continue();
void Failed();

#endif