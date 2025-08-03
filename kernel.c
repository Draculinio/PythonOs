#include "video.h"
#include "isr.h"
#include "keyboard.h"
#include "pic.h"

/*void kernel_main(void) {
    clear_screen();
    print(".----------.\n");
    print("| PythonOs |\n");
    print("----------\n");
    print_color("Welcome to the Pythonist OS!\n\n", 0x1E);
    print("Welcome Python worshiper.\n");
    print("This is a simple kernel written in C.");

    remap_pic();  // Remap the PIC to avoid conflicts with BIOS interrupts
    init_idt();
    init_keyboard();
    enable_interrupts();

    while (1) {
        asm volatile("hlt");
    }
}*/

// kernel.c
#include "video.h"
#include "isr.h"
#include "keyboard.h"
#include "pic.h"

void kernel_main(void) {
    init_idt();
    remap_pic();
    init_keyboard();
    enable_interrupts();
    clear_screen();
    print("PythonOS - Kernel started\n");
    

    while (1) {
        asm volatile ("hlt");
    }
}

