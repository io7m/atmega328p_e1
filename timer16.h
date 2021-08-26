#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

typedef struct {
  volatile uint8_t TCCRA;
  volatile uint8_t TCCRB;
  volatile uint8_t TCCRC;
  volatile uint8_t RESERVED_A;
  volatile uint8_t TCNTL;
  volatile uint8_t TCNTH;
} timer16_t;

#endif // TIMER_H
