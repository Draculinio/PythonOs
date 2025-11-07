#pragma once
#include <stdint.h>

typedef struct registers {
    uint32_t ds;                  // Data segment selector
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha
    uint32_t int_no, err_code;    // Número de interrupción y código de error (si aplica)
    uint32_t eip, cs, eflags, useresp, ss; // Pushed automáticamente por la CPU
} registers_t;

// Inicialización de la IDT
void set_idt_gate(int n, uint32_t handler);
void init_idt();
void enable_interrupts();
void disable_interrupts();

// Funciones de bajo nivel definidas en ASM
void idt_load(void* idt_ptr);
void default_handler();
void irq0_handler();
void irq1_handler();

// Nueva API: registrar handlers en C
//void register_interrupt_handler(uint8_t n, void (*handler)(registers_t *r));
void isr_handler(registers_t *r);
