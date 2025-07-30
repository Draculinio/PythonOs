#include "video.h"

void kernel_main(void) {
    clear_screen();
    print_color("Welcome to the Pythonist OS!\n\n", 0x1E);
    print("Welcome Python worshiper.\n");
    print("This is a simple kernel written in C.");
    while (1); // loop infinito
}
