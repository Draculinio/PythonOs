#include "video.h"
#include "string.h"

#define VIDEO_ADDRESS (uint16_t*)0xB8000
#define MAX_ROWS 25
#define MAX_COLS 80

#define PROMPT "> "
static int cursor_row = 0;
static int cursor_col = 0;

static void put_char_at(char c, int row, int col, char attr);

void backspace() {
    if (cursor_col > 0) {
        // Retrocede una columna y borra el carácter
        cursor_col--;
        put_char_at(' ', cursor_row, cursor_col, WHITE_ON_BLACK);
    } else if (cursor_row > 0) {
        // Retrocede a la línea anterior, última columna
        cursor_row--;
        cursor_col = MAX_COLS - 1;
        put_char_at(' ', cursor_row, cursor_col, WHITE_ON_BLACK);
    }
}

//Scroll into the console
void scroll() {
    uint16_t *video = VIDEO_ADDRESS;

    // Move files up
    for (int row = 1; row < MAX_ROWS; row++) {
        for (int col = 0; col < MAX_COLS; col++) {
            video[(row - 1) * MAX_COLS + col] = video[row * MAX_COLS + col];
        }
    }

    // Clean last line
    for (int col = 0; col < MAX_COLS; col++) {
        video[(MAX_ROWS - 1) * MAX_COLS + col] = (uint16_t)' ' | (WHITE_ON_BLACK << 8);
    }

    if (cursor_row > 0) 
        cursor_row = MAX_ROWS - 1;
    else
        cursor_row = 0;
}


// Writes a character on a position
static void put_char_at(char c, int row, int col, char attr) {
    char *video = (char*)VIDEO_ADDRESS;
    int offset = 2 * (row * MAX_COLS + col);
    video[offset] = c;
    video[offset + 1] = attr;
}

// Deletes screen
void clear_screen() {
    for (int row = 0; row < MAX_ROWS; row++) {
        for (int col = 0; col < MAX_COLS; col++) {
            put_char_at(' ', row, col, WHITE_ON_BLACK);
        }
    }
    cursor_row = 0;
    cursor_col = 0;
}

static void print_with_attr(const char *str, char attr) {
    while (*str) {
        if (*str == '\n') {
            cursor_row++;
            cursor_col = 0;
        } else {
            put_char_at(*str, cursor_row, cursor_col, attr);
            cursor_col++;
            if (cursor_col >= MAX_COLS) {
                cursor_col = 0;
                cursor_row++;
            }
        }

        if (cursor_row >= MAX_ROWS) {
            scroll();
        }

        str++;
    }
}

// Versión por defecto (blanco sobre negro)
void print(const char *str) {
    print_with_attr(str, WHITE_ON_BLACK);
}

// Versión con color custom
void print_color(const char *str, char attr) {
    print_with_attr(str, attr);
}

void print_int(int num) {
    char str[12]; // Enough for 32-bit int
    int_to_str(num, str);
    print(str);
}

void print_prompt() {
    print(PROMPT);
}

void print_hex(uint32_t num) {
    char buffer[11]; // "0x" + 8 hex + '\0'
    buffer[0] = '0';
    buffer[1] = 'x';

    for (int i = 0; i < 8; i++) {
        uint8_t nibble = (num >> ((7 - i) * 4)) & 0xF;
        if (nibble < 10)
            buffer[2 + i] = '0' + nibble;
        else
            buffer[2 + i] = 'A' + (nibble - 10);
    }

    buffer[10] = '\0';
    print(buffer);
}

