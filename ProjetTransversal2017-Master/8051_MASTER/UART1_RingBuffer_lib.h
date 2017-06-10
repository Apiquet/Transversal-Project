 #ifndef UART1_RING_BUFFER_H
 #define UART1_RING_BUFFER_H
#include <CFG_Globale.h>

void init_Serial_Buffer(void);
unsigned char serOutchar(char c);
char serInchar(void); 
unsigned int serInchar_Bin(void);
unsigned char serOutstring(char *buf);
void cfg_Clock_UART(void);
void cfg_UART0_mode1(void);


#endif