#include "video.h"
#include "isr.h"
#include "keyboard.h"
#include "pic.h"
#include "memory.h"
#include "pit.h"
#include "irq.h"
#include "sleep.h"

void kernel_main(void) {
    clear_screen();
    memory_init(0x01000000, 0x00100000); // inicializar memoria (1MB a partir de 1MB (0x100000))
    print_color("PythonOS - Kernel started\n",BLUE_ON_BLACK);
    print_color("Type 'help' for commands\n", GREEN_ON_BLACK);
    print("Version: 0.052 Alpha\n\n");
    init_idt();
    remap_pic();
    irq_init();
    pit_init(100); // Inicializar PIT a 100 Hz
    init_keyboard();
    enable_interrupts();
    print_prompt();
    
    while (1) {
        asm volatile ("hlt");
    }
}

