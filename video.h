#ifndef VIDEO_H
#define VIDEO_H

#include <stdint.h>

// Colors (Need some more definitions for different colors)
#define BLACK 0x0
#define BLUE 0x1
#define GREEN 0x2
#define CYAN 0x3
#define RED 0x4
#define MAGENTA 0x5
#define BROWN 0x6
#define LIGHT_GREY 0x7
#define DARK_GREY 0x8
#define LIGHT_BLUE 0x9
#define LIGHT_GREEN 0xA
#define LIGHT_CYAN 0xB
#define LIGHT_RED 0xC
#define LIGHT_MAGENTA 0xD
#define YELLOW 0xE
#define WHITE 0xF

#define COLOR(fg, bg) ((bg << 4) | (fg))

#define WHITE_ON_BLACK COLOR(WHITE, BLACK)
#define RED_ON_BLACK COLOR(RED, BLACK)
#define BLACK_ON_WHITE COLOR(BLACK, WHITE)
#define BLUE_ON_BLACK COLOR(BLUE, BLACK)
#define GREEN_ON_BLACK COLOR(GREEN, BLACK)
#define YELLOW_ON_BLACK COLOR(YELLOW, BLACK)
#define CYAN_ON_BLACK COLOR(CYAN, BLACK)
#define MAGENTA_ON_BLACK COLOR(MAGENTA, BLACK)

void clear_screen();
void print(const char *str);
void print_color(const char *str, char attr);
void backspace();
void print_prompt();
void print_int(int num); // This should not be in video.h, but is needed for memory.c
void int_to_str(int num, char *str); // Function to convert integer to string
void print_hex(uint32_t num);

#endif
