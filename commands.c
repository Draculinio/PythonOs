#include "commands.h"
#include "video.h"
#include "string.h"
#include "memory.h"
#include "utils.h"

void process_command(const char *input) {
    if (strcmp(input, "help") == 0) {
        print_color("PythonOS Commands Help\n", RED_ON_BLACK);
        print("Commands:\n");
        print("help - shows help\n");
        print("clear - clean screen\n");
        print("meminfo - shows memory usage\n");
        print("malloc <n> - allocates n bytes\n");
        print("free <addr> - frees memory at address\n");
        print("dump - dumps heap info\n");
        print("gdump - visual heap dump\n");
        print("allocInt <value> - allocates an int with value\n");
        print("poke <addr> <value> - writes value at address\n");
        print("peek <addr> - reads byte at address\n");
        print("peekHex <hex_addr> - reads byte at hex address\n");
        print("version - shows OS version\n");
    }
    else if (strcmp(input, "clear") == 0) {
        clear_screen();
    }
    else if(strcmp(input, "meminfo") == 0) {
        meminfo();
    }
    else if(strncmp(input, "malloc ", 7) == 0) {
        int n = k_atoi(input + 7);
        void* p = kmalloc((size_t)n);
        print("malloc -> ");
        print_int((int)(uint32_t)p);
        print("\n");
    }
    else if (strncmp(input, "free ", 5) == 0) {
        uint32_t addr = (uint32_t)atoi(input + 5); // o parseá hex si preferís
        uint32_t size = kfree((void*)addr);
        if (size) {
            print("free ok ->");
            print_int(size);
            print( " bytes at ");
            print_int(addr);
            print("\n");
        } else {
            print("free failed\n");
        }
    }
    else if (strcmp(input, "version") == 0) {
        print_color("PythonOS Version: 0.051 Alpha\n", BLUE_ON_BLACK);
    }
    else if (strcmp(input, "dump") == 0) {
        dump_heap();
    }
    else if(strcmp(input, "gdump") == 0) {
        dump_heap_visual();
    }
    else if(strncmp(input, "allocInt ",9) == 0) {
        int n = atoi(input + 9);
        int* p = alloc_int(n);
        if (p) {
            print("int reserved in ");
            print_hex((uint32_t)p);
            print(" with value ");
            print_int(*p);
            print("\n");
        }
    }
    else if (strncmp(input, "poke ", 5) == 0) {
        uint32_t addr, value;
        if (sscanf_simple(input + 5, "%u %u", &addr, &value) == 2) {
            poke(addr, value);
            print("poke ok\n");
        }
    }
    else if (strncmp(input, "peek ", 5) == 0) {
        uint32_t addr;
        if (sscanf_simple(input + 5, "%u", &addr, NULL) == 1) {
            unsigned char v = peek(addr);
            print("peek -> ");
            print_int(v);
            print("\n");
        }
    }
    else if(strncmp(input, "peekHex ", 8) == 0) {
        uint32_t addr = hex_to_int(input + 8);
        int value = peek(addr);
        print("Value at ");
        print(input + 8);  // Muestra la dirección tal como la escribiste
        print(" is ");
        print_int(value);
        print(" (0x");
        print_hex(value);
        print(")\n");
    }

    else {
        print("Command not found: ");
        print(input);
        print("\n");
    }
}
