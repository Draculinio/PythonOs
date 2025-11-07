#include "isr.h"
#include "video.h"     // para print_color(), print_int()
#include <stddef.h>    // para NULL

#define IDT_ENTRIES 256

// ----- Estructuras de IDT -----
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

// ----- Tabla de handlers de C -----
static void (*interrupt_handlers[IDT_ENTRIES])(registers_t *r) = { 0 };

// ----- Referencias externas -----
extern void idt_load(void* idt_ptr);
extern void default_handler();
extern void irq0_handler();
extern void irq1_handler();

// ----- IDT base -----
void set_idt_gate(int n, uint32_t handler) {
    idt[n].base_low = handler & 0xFFFF;
    idt[n].sel = 0x08;  // selector de segmento de código (CS)
    idt[n].always0 = 0;
    idt[n].flags = 0x8E; // presente, nivel 0, interrupt gate 32 bits
    idt[n].base_high = (handler >> 16) & 0xFFFF;
}

void init_idt() {
    for (int i = 0; i < IDT_ENTRIES; i++) {
        set_idt_gate(i, (uint32_t)default_handler);
    }

    // IRQs básicas
    set_idt_gate(32, (uint32_t)irq0_handler); // Timer (PIT)
    set_idt_gate(33, (uint32_t)irq1_handler); // Teclado

    idtp.limit = sizeof(idt) - 1;
    idtp.base = (uint32_t)&idt;

    idt_load(&idtp);

    print_color("IDT initialized (256 entries)\n", GREEN_ON_BLACK);
}

// ----- Control global -----
void enable_interrupts() { asm volatile ("sti"); }
void disable_interrupts() { asm volatile ("cli"); }

// ----- Registro de handlers dinámicos -----
//void register_interrupt_handler(uint8_t n, void (*handler)(registers_t *r)) {
//    interrupt_handlers[n] = handler;
//}

// ----- ISR handler global -----
void isr_handler(registers_t *r) {
    if (interrupt_handlers[r->int_no]) {
        interrupt_handlers[r->int_no](r);
    } else {
        print_color("Unhandled interrupt: ", RED_ON_BLACK);
        print_int(r->int_no);
        print("\n");
    }
}