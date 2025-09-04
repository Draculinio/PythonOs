#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

int sscanf_simple(const char* str, const char* fmt, uint32_t* a, uint32_t* b);
uint32_t hex_to_int(char* hex_str);

#endif

