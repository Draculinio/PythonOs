#pragma once
#include <stdint.h>

void idt_load(void* idt_ptr);

void default_handler();
void irq0_handler();
void irq1_handler();

void set_idt_gate(int n, uint32_t handler);
void init_idt();
void enable_interrupts();
void disable_interrupts();
