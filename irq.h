#ifndef IRQ_H
#define IRQ_H

#include <stdint.h>
#include "isr.h"

void irq_init(void);
void irq_handler(registers_t *r);

typedef void (*isr_t)(registers_t*);
void register_interrupt_handler(uint8_t n, isr_t handler);

#endif
