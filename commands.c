#include "commands.h"
#include "video.h"
#include "string.h"

void process_command(const char *input) {
    if (strcmp(input, "help") == 0) {
        print_color("PythonOS Commands Help\n", RED_ON_BLACK); // 'G' for green
        print("Commands:\n");
        print("help - shows help\n");
        print("clear - clean screen\n");
    }
    else if (strcmp(input, "clear") == 0) {
        clear_screen();
    }
    else {
        print("Command not found: ");
        print(input);
        print("\n");
    }
}
