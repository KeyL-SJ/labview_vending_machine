#include <reg52.h>

void usart_init(void);
void UART_send_byte(unsigned char dat);
void UART_send_string(unsigned char *buf);