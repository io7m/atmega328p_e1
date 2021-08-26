#include "usart.h"

static const uint8_t TXEN_BIT = 0b00001000;
static const uint8_t RXEN_BIT = 0b00010000;
static const uint8_t UCSZn0_BIT = 0b00000010;
static const uint8_t UCSZn1_BIT = 0b00000100;
static const uint8_t UDREn_BIT = 0b00100000;

static uint16_t usart_ubrr(uint32_t cpu_clock_hz, uint32_t baud) {
  return (cpu_clock_hz / (16 * baud)) - 1;
}

void usart_init(usart_t *restrict const usart, uint16_t baud) {

  /*
   * Configure the baud rate based on a 16mhz clock.
   */

  const uint16_t ubrr = usart_ubrr(16000000, baud);
  usart->UBRRH = (ubrr >> 8);
  usart->UBRRL = ubrr & 0xff;

  /*
   * Enable the sender and receiver.
   */

  usart->UCSRB = RXEN_BIT | TXEN_BIT;

  /*
   * Specify 8-bit bytes.
   */

  usart->UCSRC = UCSZn0_BIT | UCSZn1_BIT;
}

void usart_put_char(usart_t *restrict const usart, uint8_t data) {

  /*
   * Wait for the transmission buffer to become ready.
   */

  while ((usart->UCSRA & UDREn_BIT) == 0)
    ;
  usart->UDR = data;
}

void usart_put_string(usart_t *restrict const usart, const char *const text) {
  const char *ptr = text;
  for (;;) {
    if (*ptr == 0) {
      break;
    }
    usart_put_char(usart, *ptr);
    ++ptr;
  }
}

void usart_put_stringf(usart_t *restrict const usart,
                       const __flash char *const text) {
  const __flash char *ptr = text;
  for (;;) {
    if (*ptr == 0) {
      break;
    }
    usart_put_char(usart, *ptr);
    ++ptr;
  }
}
