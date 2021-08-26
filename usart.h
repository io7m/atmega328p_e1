#ifndef USART_H
#define USART_H

#include <stdint.h>

typedef struct {
  volatile uint8_t UCSRA;
  volatile uint8_t UCSRB;
  volatile uint8_t UCSRC;
  volatile uint8_t RESERVED_A;
  volatile uint8_t UBRRL;
  volatile uint8_t UBRRH;
  volatile uint8_t UDR;
} usart_t;

_Static_assert(sizeof(usart_t) == 7, "usart_t must be correct size");

void usart_init(usart_t *restrict const usart, uint16_t baud);

void usart_put_char(usart_t *restrict const usart, uint8_t data);

void usart_put_string(usart_t *restrict const usart, const char *const text);

void usart_put_stringf(usart_t *restrict const usart,
                       const __flash char *const text);

#endif // USART_H
