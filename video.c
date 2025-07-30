#include "video.h"

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80

// Colores por defecto (blanco sobre negro)
#define WHITE_ON_BLACK 0x0F

static int cursor_row = 0;
static int cursor_col = 0;

// Escribe un caracter en una posición dada
static void put_char_at(char c, int row, int col, char attr) {
    char *video = (char*)VIDEO_ADDRESS;
    int offset = 2 * (row * MAX_COLS + col);
    video[offset] = c;
    video[offset + 1] = attr;
}

// Borra la pantalla entera
void clear_screen() {
    for (int row = 0; row < MAX_ROWS; row++) {
        for (int col = 0; col < MAX_COLS; col++) {
            put_char_at(' ', row, col, WHITE_ON_BLACK);
        }
    }
    cursor_row = 0;
    cursor_col = 0;
}

// Imprime un string en la posición actual
void print(const char *str) {
    while (*str) {
        if (*str == '\n') {
            cursor_row++;
            cursor_col = 0;
        } else {
            put_char_at(*str, cursor_row, cursor_col, WHITE_ON_BLACK);
            cursor_col++;
            if (cursor_col >= MAX_COLS) {
                cursor_col = 0;
                cursor_row++;
            }
        }

        if (cursor_row >= MAX_ROWS) {
            cursor_row = 0;  // Si se llena la pantalla, vuelve arriba (scroll simple)
        }

        str++;
    }
}

//Imprime texto con un color específico
void print_color(const char *str, char attr) {
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
            cursor_row = 0;  // Simple wrap (scroll lo veremos después)
        }

        str++;
    }
}
