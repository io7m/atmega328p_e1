#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

typedef struct {
  volatile uint8_t TCCRA;
  volatile uint8_t TCCRB;
  volatile uint8_t TCNT;
} timer8_t;

typedef struct {
  volatile uint8_t OCRA;
  volatile uint8_t OCRB;
} timer8_output_compare_t;

#endif // TIMER_H
