#include "pit.h"
#include "port_io.h"      // para outb()
#include "video.h"      // para print o print_color
#include "isr.h"        // para registrar el handler
#include "irq.h"
#include <stdint.h>

static uint32_t tick_count = 0;


void timer_interrupt_handler(void) {
    tick_count++;
}

void pit_init(uint32_t frequency) {
    uint32_t divisor = PIT_FREQUENCY / frequency;

    // Comando de control: canal 0, modo 3 (square wave), acceso low/high
    outb(0x43, 0x36);

    // Enviar divisor en dos partes
    uint8_t low = (uint8_t)(divisor & 0xFF);
    uint8_t high = (uint8_t)((divisor >> 8) & 0xFF);

    outb(0x40, low);
    outb(0x40, high);

    // Registrar el handler para IRQ0
    //register_interrupt_handler(32, pit_callback);

    print_color("PIT initialized at ", GREEN_ON_BLACK);
    print_int(frequency);
    print(" Hz\n");
}

uint32_t pit_get_ticks(void) {
    return tick_count;
}
