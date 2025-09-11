#include "utils.h"

// sscanf_simple: soporta formato "%u" o "%u %u"
// b puede ser NULL si solo querés leer un entero
int sscanf_simple(const char* str, const char* fmt, uint32_t* a, uint32_t* b) {
    if (fmt[0] == '%' && fmt[1] == 'u') {
        int n = 0;
        uint32_t tmp = 0;

        // primer número
        while (*str >= '0' && *str <= '9') {
            tmp = tmp * 10 + (*str - '0');
            str++;
            n++;
        }
        if (n > 0) {
            if (a) *a = tmp;
        } else {
            return 0; // no se parseó nada
        }

        // saltar espacios
        while (*str == ' ') str++;

        // segundo número (opcional)
        if (*str >= '0' && *str <= '9') {
            tmp = 0;
            n = 0;
            while (*str >= '0' && *str <= '9') {
                tmp = tmp * 10 + (*str - '0');
                str++;
                n++;
            }
            if (n > 0 && b) {
                *b = tmp;
                return 2;
            }
        }

        return 1;
    }
    return 0;
}


uint32_t hex_to_int(const char* hex_str) {
    uint32_t result = 0;
    int i = 0;
    
    // Saltar "0x" si está presente
    if (hex_str[0] == '0' && (hex_str[1] == 'x' || hex_str[1] == 'X')) {
        i = 2;
    }
    
    while (hex_str[i] != '\0' && hex_str[i] != ' ' && hex_str[i] != '\n') {
        char c = hex_str[i];
        if (c >= '0' && c <= '9') {
            result = result * 16 + (c - '0');
        } else if (c >= 'A' && c <= 'F') {
            result = result * 16 + (c - 'A' + 10);
        } else if (c >= 'a' && c <= 'f') {
            result = result * 16 + (c - 'a' + 10);
        } else {
            break;  // Carácter inválido
        }
        i++;
    }
    return result;
}