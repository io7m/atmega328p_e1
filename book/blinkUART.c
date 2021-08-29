#include <stdint.h>

volatile uint8_t * const UCSR0A = (volatile uint8_t *) 0x00c0;
volatile uint8_t * const UCSR0B = (volatile uint8_t *) 0x00c1;
volatile uint8_t * const UCSR0C = (volatile uint8_t *) 0x00c2;
volatile uint8_t * const UBRR0L = (volatile uint8_t *) 0x00c4;
volatile uint8_t * const UBRR0H = (volatile uint8_t *) 0x00c5;
volatile uint8_t * const UDR0 = (volatile uint8_t *) 0x00c6;

static const uint8_t TXEN_BIT = 0b00001000;
static const uint8_t UCSZn0_BIT = 0b00000010;
static const uint8_t UCSZn1_BIT = 0b00000100;
static const uint8_t UDREn_BIT = 0b00100000;

static uint16_t
usart_ubrr(uint32_t cpu_clock_hz, uint32_t baud) {
  return (cpu_clock_hz / (16 * baud)) - 1;
}

void
usart_init(uint32_t baud)
{
  /*
   * Configure the baud rate based on a 16mhz clock.
   */

  const uint16_t ubrr = usart_ubrr(16000000, baud);
  *UBRR0H = (ubrr >> 8);
  *UBRR0L = ubrr & 0xff;

  /*
   * Enable the sender.
   */

  *UCSR0B = TXEN_BIT;

  /*
   * Specify 8-bit bytes.
   */

  *UCSR0C = UCSZn0_BIT | UCSZn1_BIT;
}

void usart_put_char(uint8_t data) {

  /*
   * Wait for the transmission buffer to become ready.
   */

  while ((*UCSR0A & UDREn_BIT) == 0)
    ;

  *UDR0 = data;
}

void usart_put_string(const char *text)
{
  const char *ptr = text;
  for (;;) {
    if (*ptr == 0) {
      break;
    }
    usart_put_char(*ptr);
    ++ptr;
  }
}

volatile uint8_t * const TCCR1B = (volatile uint8_t *) 0x0081;
volatile uint8_t * const TCNT1L = (volatile uint8_t *) 0x0084;
volatile uint8_t * const TCNT1H = (volatile uint8_t *) 0x0085;

static const uint16_t ticks_per_second = 15625;

void
pause (void)
{
  // Select a /1024 prescaler.
  *TCCR1B = 0b00000101;
  *TCNT1H = 0;
  *TCNT1L = 0;

  for (;;) {
    uint16_t time = 0;
    time |= *TCNT1L;
    time |= *TCNT1H << 8;

    if (time >= ticks_per_second) {
      return;
    }
  }
}

volatile uint8_t * const PORTB = (volatile uint8_t *) 0x0025;
volatile uint8_t * const DDRB = (volatile uint8_t *) 0x0024;

int
main (void)
{
  *DDRB = 0b11111111;

  usart_init(9600);
  usart_put_string("start\n");

  for (;;) {
    *PORTB = 1;
    usart_put_string("led on\n");
    pause();
    *PORTB = 0;
    usart_put_string("led off\n");
    pause();
  }
}

