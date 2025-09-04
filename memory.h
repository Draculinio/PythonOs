#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>
#include <stdint.h>

void memory_init(uint32_t start, uint32_t size);
void* kmalloc(size_t size);
uint32_t kfree(void* ptr);
void dump_heap();
void dump_heap_visual(void);
int* alloc_int(int value);
void poke(uint32_t addr, int value);
int peek(uint32_t addr);

void meminfo(void); // imprimir memoria libre/ocupada

#endif
