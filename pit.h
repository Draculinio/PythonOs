#ifndef PIT_H
#define PIT_H

#include <stdint.h>

// Frecuencia base del PIT (1.193182 MHz)
#define PIT_FREQUENCY 1193182

// Configura el PIT para que genere interrupciones a la frecuencia dada (en Hz)
void pit_init(uint32_t frequency);

// Devuelve el número de ticks desde el arranque
uint32_t pit_get_ticks(void);

void timer_interrupt_handler(void);

#endif