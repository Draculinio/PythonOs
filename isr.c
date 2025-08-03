#include "isr.h"

#define IDT_ENTRIES 256

struct idt_entry {
    uint16_t base_low;
    uint16_t sel;
    uint8_t always0;
    uint8_t flags;
    uint16_t base_high;
} __attribute__((packed));

struct idt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

static struct idt_entry idt[IDT_ENTRIES];
static struct idt_ptr idtp;

extern void idt_load(void* idt_ptr);
extern void default_handler();
extern void irq0_handler();
extern void irq1_handler();

void set_idt_gate(int n, uint32_t handler) {
    idt[n].base_low = handler & 0xFFFF;
    idt[n].sel = 0x08;  // selector de segmento de código
    idt[n].always0 = 0;
    idt[n].flags = 0x8E; // presente, nivel 0, interrupt gate 32 bits
    idt[n].base_high = (handler >> 16) & 0xFFFF;
}

void init_idt() {
    // Primero cargar default_handler para todas las entradas
    for (int i = 0; i < IDT_ENTRIES; i++) {
        set_idt_gate(i, (uint32_t)default_handler);
    }
    // Cargar handlers de IRQ0 (timer) e IRQ1 (teclado)
    set_idt_gate(32, (uint32_t)irq0_handler);
    set_idt_gate(33, (uint32_t)irq1_handler);

    idtp.limit = sizeof(idt) - 1;
    idtp.base = (uint32_t)&idt;

    idt_load(&idtp);
}

void enable_interrupts() {
    asm volatile ("sti");
}

void disable_interrupts() {
    asm volatile ("cli");
}
