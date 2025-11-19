#include "sleep.h"
#include "pit.h"
#include "video.h"
#include "isr.h"

void sleep_ms(uint32_t ms) {
    uint32_t start = pit_get_ticks();
    uint32_t ticks_to_wait = (ms * 100) / 1000;
    
    // Asegurar que las interrupciones están habilitadas
    enable_interrupts();
    
    while ((pit_get_ticks() - start) < ticks_to_wait) {
        asm volatile("hlt");  // Esperar interrupción
    }
}