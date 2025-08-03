; boot.s - Cabecera Multiboot y configuración inicial

; Constantes Multiboot
MAGIC    equ 0x1BADB002
FLAGS    equ (1 << 0) | (1 << 1)    ; Alinear + pedir info memoria
CHECKSUM equ -(MAGIC + FLAGS)

section .multiboot
align 4
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

section .bss
align 16
stack_bottom:
    resb 16384  ; 16 KB de stack
stack_top:

section .data
; GDT más simple y seguro
gdt_start:
    ; Entrada nula (requerida)
    dq 0

    ; Segmento de código (0x08) - flat 4GB
    dw 0xFFFF       ; Límite 0-15
    dw 0x0000       ; Base 0-15
    db 0x00         ; Base 16-23
    db 10011010b    ; Acceso: presente, DPL=0, código, ejecutable, readable
    db 11001111b    ; Granularidad: 4KB, 32-bit, límite 16-19 = 1111
    db 0x00         ; Base 24-31

    ; Segmento de datos (0x10) - flat 4GB
    dw 0xFFFF       ; Límite 0-15
    dw 0x0000       ; Base 0-15
    db 0x00         ; Base 16-23
    db 10010010b    ; Acceso: presente, DPL=0, datos, writable
    db 11001111b    ; Granularidad: 4KB, 32-bit, límite 16-19 = 1111
    db 0x00         ; Base 24-31

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1  ; Tamaño
    dd gdt_start                ; Dirección

section .text
global _start
_start:
    ; IMPORTANTE: Deshabilitar interrupciones inmediatamente
    cli

    ; Configurar stack
    mov esp, stack_top

    ; Cargar nuestro GDT
    lgdt [gdt_descriptor]

    ; Saltar para cargar CS con el nuevo selector
    jmp 0x08:reload_segments

reload_segments:
    ; Cargar selectores de datos
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; Llamar al kernel (con interrupciones deshabilitadas)
    extern kernel_main
    call kernel_main

.hang:
    cli
    hlt
    jmp .hang