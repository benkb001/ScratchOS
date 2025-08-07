print_bios: 
    pusha       ; push all registers to stack 

    print_bios_cur: 
        
        ;assume bx has the address of the first char 
        mov al, [bx]

        cmp al, 0x00 
        je print_bios_end   ; end if reached null terminating character 
        
        ;put 0x0e in ah to later make BIOS interrupt call 
        mov ah, 0x0e
        int 0x10 ; call BIOS interrupt for print

        add bx, 1 ; add 1 byte to bx so it will then assign al to the next char 
        jmp print_bios_cur
    print_bios_end: 
        popa
        ret