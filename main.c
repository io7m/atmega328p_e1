#include "io_register.h"
#include "timer16.h"
#include "usart.h"

static io_register_t *const PORTB = (io_register_t *)0x0023;
// static volatile io_register_t *const PORTC = (io_register_t *)0x0026;
// static volatile io_register_t *const PORTD = (io_register_t *)0x0029;
static usart_t *const USART0 = (usart_t *)0x00c0;
// static timer8_t *const TIMER0 = (timer8_t *)0x0044;
static timer16_t *const TIMER1 = (timer16_t *)0x0080;

static void wait_one_second() {

  /*
   * Specify a /1024 prescaler for the 16mhz clock. This will yield 1 second =
   * 15625 ticks.
   */

  TIMER1->TCCRB = 0b00000101;
  TIMER1->TCNTH = 0;
  TIMER1->TCNTL = 0;

  for (;;) {
    uint16_t time = 0;
    time |= TIMER1->TCNTL;
    time |= TIMER1->TCNTH << 8;

    if (time >= 15625) {
      break;
    }
  }
}

const __flash char msg_start[] = "i: start\n";
const __flash char msg_tick[] = "i: tick\n";

static uint8_t count;

int main(void) {
  PORTB->DDR |= 1;
  PORTB->PORT &= ~1;

  usart_init(USART0, 9600);
  usart_put_stringf(USART0, msg_start);

  for (;;) {
    PORTB->PORT |= 1;
    wait_one_second();
    PORTB->PORT &= ~1;
    wait_one_second();
    usart_put_stringf(USART0, msg_tick);
    ++count;
  }
  return 0;
}
