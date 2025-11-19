#include "irq.h"
#include "port_io.h"
#include "video.h"

#define IRQ_BASE 32
static isr_t interrupt_handlers[256] = { 0 };
void register_interrupt_handler(uint8_t n, isr_t handler) {
    interrupt_handlers[n] = handler;
}
void irq_init(void) {
    // Remapear PIC maestro y esclavo
    outb(0x20, 0x11);
    outb(0xA0, 0x11);

    outb(0x21, 0x20); // maestro -> 0x20-0x27
    outb(0xA1, 0x28); // esclavo  -> 0x28-0x2F

    outb(0x21, 0x04);
    outb(0xA1, 0x02);

    outb(0x21, 0x01);
    outb(0xA1, 0x01);

    outb(0x21, 0x0);
    outb(0xA1, 0x0);

    print_color("PIC remapped to 0x20–0x2F\n", GREEN_ON_BLACK);
}

// Handler genérico de interrupciones de hardware
void irq_handler(registers_t *r) {
    // Llamar al handler registrado si existe
    if (r->int_no < 256 && interrupt_handlers[r->int_no]) {
        isr_t handler = interrupt_handlers[r->int_no];
        handler(r);
    }
    // End of Interrupt (EOI)
    if (r->int_no >= 40)
        outb(0xA0, 0x20); // EOI esclavo

    outb(0x20, 0x20);     // EOI maestro
}
