ENTRY(_start)

SECTIONS
{
    /* GRUB carga el kernel en 1MB */
    . = 1M;

    /* Código (incluye multiboot y _start) */
    .text ALIGN(4K) :
    {
        KEEP(*(.multiboot))     /* Mantiene cabecera multiboot */
        *(.text*)
    }

    .rodata ALIGN(4K) :
    {
        *(.rodata*)
    }

    .data ALIGN(4K) :
    {
        *(.data*)
    }

    .bss ALIGN(4K) :
    {
        __bss_start = .;
        *(.bss*)
        *(COMMON)
        __bss_end = .;
    }
}

