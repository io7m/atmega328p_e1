#include <stdint.h>

void
pause (void)
{
  for (volatile uint8_t z = 0; z < 100; ++z) {
    for (volatile uint8_t y = 0; y < 100; ++y) {
      for (volatile uint8_t z = 0; z < 100; ++z) {
        // Do nothing
      }
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

