 #ifndef UART0_RING_BUFFER_H
 #define UART0_RING_BUFFER_H
#include <CFG_Globale.h>

void init_Serial_Buffer(void);
unsigned char serOutchar(char c);
char serInchar(void); 
unsigned int serInchar_Bin(void);
unsigned char serOutstring(char *buf);
void cfg_Clock_UART(void);
void cfg_UART0_mode1(void);

void init_Serial_Buffer_1(void);
unsigned char serOutchar_1(char c);
char serInchar_1(void); 
unsigned int serInchar_Bin_1(void);
unsigned char serOutstring_1(char *buf);
void cfg_UARTS_mode1(void);
#endif