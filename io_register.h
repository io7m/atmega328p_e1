#ifndef IO_REGISTER_H
#define IO_REGISTER_H

#include <stdint.h>

typedef struct {
  volatile uint8_t PIN;
  volatile uint8_t DDR;
  volatile uint8_t PORT;
} io_register_t;

_Static_assert(sizeof(io_register_t) == 3,
               "sizeof io_register_t must be correct");

#endif
