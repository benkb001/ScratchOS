[BITS 16]                   ; begin with 16 bit mode 

switch_to_pm:               ; Switching into 32 bit protected mode, this requires a few steps 
    
    mov bx, MSG_SWITCH_PM   ;Prepare to print with bios by moving message into bx
    call print_bios 

    cli                     ; This disables interrupts, but it does leave the Interrupt vector table unaffected 

    lgdt[gdt_descriptor]    ; this loads the gdt, defined in global_descriptor_table.asm 

                            
    mov eax, cr0            ; the next 3 lines just set the first bit in cr0 to 1, signaling to the cpu that we're now in 32 bit mode
    or eax, 0x1
    mov cr0, eax 

    jmp CODE_SEG:init_pm    ;far jump into code seg 
                            ;important ! We will not be returning from here 
                            ;the far jump is also necessary to flush the cpu's expected instructions 
                            ; Reason we can use init_pm is basically because all code currently is in 1 flat segment 
[bits 32]                   ; We can safely move into 32 bit mode now ! 

init_pm: 
    mov ax, DATA_SEG 
    mov ds, ax
    mov ss, ax
    mov es, ax 
    mov fs, ax 
    mov gs, ax 

    mov ebp, 0x90000
    mov esp, ebp

    call BEGIN_PM 

MSG_SWITCH_PM db "Began switch to protected mode",0 