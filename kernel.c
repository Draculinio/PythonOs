#include "video.h"
#include "isr.h"
#include "keyboard.h"
#include "pic.h"
#include "memory.h"

void kernel_main(void) {
    init_idt();
    remap_pic();
    init_keyboard();
    enable_interrupts();
    clear_screen();
    memory_init(0x01000000, 0x00100000); // inicializar memoria (1MB a partir de 1MB (0x100000))
    //void* a = kmalloc(256);
    //void* b = kmalloc(128);
    meminfo();
    print_color("PythonOS - Kernel started\n",BLUE_ON_BLACK);
    print_color("Type 'help' for commands\n", GREEN_ON_BLACK);
    print("Version: 0.051 Alpha\n\n");
    print_prompt();
    

    while (1) {
        asm volatile ("hlt");
    }
}

