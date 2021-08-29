#include <stdint.h>

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
  *DDRB = 1;

  for (;;) {
    *PORTB = 1;
    pause();
    *PORTB = 0;
    pause();
  }
}

