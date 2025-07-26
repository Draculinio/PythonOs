; boot.s - Cabecera Multiboot y salto al kernel (NASM syntax)

; Constantes Multiboot
MAGIC    equ 0x1BADB002
FLAGS    equ (1 << 0) | (1 << 1)    ; Alinear + pedir info memoria
CHECKSUM equ -(MAGIC + FLAGS)

section .multiboot
align 4
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

section .text
global _start
_start:
    extern kernel_main
    call kernel_main
.hang:
    jmp .hang
