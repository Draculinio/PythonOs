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
    print_color("PythonOS - Kernel started\n",BLUE_ON_BLACK);
    print_color("Type 'help' for commands\n", GREEN_ON_BLACK);
    print("Version: 0.04 Alpha\n\n");
    print_prompt();
    

    while (1) {
        asm volatile ("hlt");
    }
}

