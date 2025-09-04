#include <stddef.h>
#include "string.h"

int strcmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

//compare up to n characters of two strings
int strncmp(const char* s1, const char* s2, size_t n) {
    while (n > 0 && *s1 && (*s1 == *s2)) {
        s1++;
        s2++;
        n--;
    }
    if (n == 0) {
        return 0; // son iguales hasta n caracteres
    }
    return *(unsigned char*)s1 - *(unsigned char*)s2;
}

// Returns the length of the string (not including the null terminator)
size_t strlen(const char* str) {
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

// Converts a string to an integer (handles optional leading '+' or '-' sign)
int atoi(const char* str) {
    int result = 0;
    int sign = 1;

    // manejar signo opcional
    if (*str == '-') {
        sign = -1;
        str++;
    } else if (*str == '+') {
        str++;
    }

    while (*str >= '0' && *str <= '9') {
        result = result * 10 + (*str - '0');
        str++;
    }
    return result * sign;
}

// Simple version of atoi that only handles positive numbers
int k_atoi(const char *str) {
    int result = 0;
    while (*str) {
        if (*str >= '0' && *str <= '9') {
            result = result * 10 + (*str - '0');
        } else {
            break; // dejamos de leer al primer caracter no dígito
        }
        str++;
    }
    return result;
}

void int_to_str(int num, char *str) {
    int i = 0;
    int is_negative = 0;

    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }

    if (num < 0) {
        is_negative = 1;
        num = -num;
    }

    while (num != 0) {
        int rem = num % 10;
        str[i++] = rem + '0';
        num /= 10;
    }

    if (is_negative) {
        str[i++] = '-';
    }

    str[i] = '\0';

    // invertir el string
    int start = 0, end = i - 1;
    while (start < end) {
        char tmp = str[start];
        str[start] = str[end];
        str[end] = tmp;
        start++;
        end--;
    }
}