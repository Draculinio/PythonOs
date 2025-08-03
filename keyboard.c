#include "keyboard.h"
#include "video.h"
#include "port_io.h"
#include <stdint.h>

#define PORT_DATA 0x60

static char scancode_table[128] = {
    0,  27, '1','2','3','4','5','6','7','8','9','0','-','=', '\b',
    '\t', 'q','w','e','r','t','y','u','i','o','p','[',']','\n', 0,
    'a','s','d','f','g','h','j','k','l',';','\'','`',   0,'\\',
    'z','x','c','v','b','n','m',',','.','/',   0, '*',   0,' '
};


void keyboard_interrupt() {
    uint8_t scancode = inb(PORT_DATA);
    if (!(scancode & 0x80)) {
        char c = scancode_table[scancode];
        if (c) {
            char str[2] = {c, '\0'};
            print(str);
        }
    }
    // El EOI lo manda irq1_handler.asm
}

void init_keyboard() {
    // Quitar máscara IRQ1 para habilitar teclado
    uint8_t mask = inb(0x21);
    mask &= ~(1 << 1);
    asm volatile ("outb %0, %1" :: "a"(mask), "dN"(0x21));
}