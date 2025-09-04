// string.h
#ifndef STRING_H
#define STRING_H

typedef unsigned long size_t;

int strcmp(const char *s1, const char *s2);
int strncmp(const char* s1, const char* s2, size_t n);
size_t strlen(const char* str);
int atoi(const char* str);
int k_atoi(const char *str);
void int_to_str(int num, char *str);
#endif
