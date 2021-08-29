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

volatile uint8_t * const PORTD = (volatile uint8_t *) 0x002B;
volatile uint8_t * const DDRD = (volatile uint8_t *) 0x002A;

int
main (void)
{
  *DDRD = 0b11111111;

  for (;;) {
    *PORTD = 0b11111111;
    pause();
    *PORTD = 0;
    pause();
  }
}

