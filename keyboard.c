#include "keyboard.h"
#include "video.h"
#include "port_io.h"
#include <stdint.h>
#include "commands.h"
#include <stdbool.h>

#define PORT_DATA 0x60
#define MAX_INPUT 128

char input_buffer[MAX_INPUT];
int input_length = 0;
// Variables para estados
static bool shift_pressed = false;
static bool caps_lock = false;
static uint8_t index = 0;

// Tabla normal
static char scancode_table[128] = {
    0,  27, '1','2','3','4','5','6','7','8','9','0','-','=', '\b',
    '\t', 'q','w','e','r','t','y','u','i','o','p','[',']','\n', 0,
    'a','s','d','f','g','h','j','k','l',';','\'','`',   0,'\\',
    'z','x','c','v','b','n','m',',','.','/',   0, '*',   0,' '
};

// Tabla con shift presionado
static char scancode_table_shift[128] = {
    0,  27, '!','@','#','$','%','^','&','*','(',')','_','+', '\b',
    '\t', 'Q','W','E','R','T','Y','U','I','O','P','{','}','\n', 0,
    'A','S','D','F','G','H','J','K','L',':','"','~',   0,'|',
    'Z','X','C','V','B','N','M','<','>','?',   0, '*',   0,' '
};

void keyboard_interrupt() {
    uint8_t scancode = inb(PORT_DATA);

    // Tecla presionada
    if (!(scancode & 0x80)) {
        if (scancode == 0x2A || scancode == 0x36) { // Shift presionado
            shift_pressed = true;
            return;
        }

        if (scancode == 0x3A) { // Caps Lock
            caps_lock = !caps_lock;
            return;
        }

        char c;
        if (shift_pressed) {
            c = scancode_table_shift[scancode];
        } else {
            c = scancode_table[scancode];
            if (caps_lock && c >= 'a' && c <= 'z') {
                c -= 32; // convertir a mayúscula
            }
        }

        if (c) {
            if (c == '\b') {
                if (index > 0) {
                    index--;
                    backspace(); // borra en pantalla
                }
            } 
            else if (c == '\n') {
                input_buffer[index] = '\0'; // fin de string
                print("\n");
                process_command(input_buffer); // procesar comando
                index = 0; // reset buffer
                print_prompt();
            } 
            else {
                if (index < MAX_INPUT - 1) {
                    input_buffer[index++] = c;
                    char str[2] = {c, '\0'};
                    print(str);
                }
            }
        }
    }
    // Tecla soltada
    else {
        uint8_t make_code = scancode & 0x7F;
        if (make_code == 0x2A || make_code == 0x36) { // Shift soltado
            shift_pressed = false;
        }
    }
}

void init_keyboard() {
    uint8_t mask = inb(0x21);
    mask &= ~(1 << 1); // habilitar IRQ1
    asm volatile ("outb %0, %1" :: "a"(mask), "dN"(0x21));
}
