#include <stdint.h>
#include "port_io.h"

#define PIC1_COMMAND 0x20
#define PIC1_DATA    0x21
#define PIC2_COMMAND 0xA0
#define PIC2_DATA    0xA1

#define ICW1_INIT    0x10
#define ICW1_ICW4    0x01
#define ICW4_8086    0x01

void remap_pic() {
    uint8_t a1 = inb(PIC1_DATA);
    uint8_t a2 = inb(PIC2_DATA);

    outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);

    outb(PIC1_DATA, 0x20); // Offset PIC1 (IRQ 0-7) -> interrupciones 32-39
    outb(PIC2_DATA, 0x28); // Offset PIC2 (IRQ 8-15) -> interrupciones 40-47

    outb(PIC1_DATA, 4);    // Tell PIC1 about PIC2 at IRQ2
    outb(PIC2_DATA, 2);    // Tell PIC2 its cascade identity

    outb(PIC1_DATA, ICW4_8086);
    outb(PIC2_DATA, ICW4_8086);

    // Restore masks
    outb(PIC1_DATA, a1);
    outb(PIC2_DATA, a2);
}

void pic_clear_mask(uint8_t irq) {
    uint16_t port;
    uint8_t value;

    if (irq < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        irq -= 8;
    }
    value = inb(port) & ~(1 << irq);
    outb(port, value);
}
