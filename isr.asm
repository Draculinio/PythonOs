[BITS 32]
global idt_load
global irq1_handler
global default_handler
global irq0_handler

extern keyboard_interrupt
extern timer_interrupt_handler

idt_load:
    push ebp
    mov ebp, esp
    mov eax, [ebp+8]
    lidt [eax]
    pop ebp
    ret

default_handler:
    pusha
    cli
    hlt
    popa
    iretd

irq0_handler:
    pusha
    
    call timer_interrupt_handler
    
    mov al, 0x20
    out 0x20, al
    popa
    iretd

irq1_handler:
    pusha
    
    call keyboard_interrupt

    mov al, 0x20
    out 0x20, al
    popa
    iretd
