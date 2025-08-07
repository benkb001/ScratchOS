[bits 32]

VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f

print: 
    pushad       ; push all registers to stack 
    mov edx, VIDEO_MEMORY ; put the address of start of video mem into edx

    print_cur: 
        ;assume ebx has the address of the first char 

        mov al, [ebx]
        mov ah, WHITE_ON_BLACK
        cmp al, 0x00
        je end   ; end if reached null terminating character 

        mov [edx], ax ; put the current char into the current vidmem area 

        add ebx, 1 ; add 1 byte to bx so it will then assign al to the next char 
        add edx, 2 ; add 2 bytes to edx so it will point to next space in video mem
        jmp print_cur
    end: 
        popad
        ret