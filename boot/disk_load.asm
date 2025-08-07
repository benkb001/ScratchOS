;load DH sectors to ES:BX from drive DL 
disk_load: 
    push dx                 ;Store on stack how many sectors were requested

    mov ah, 0x02            ;Set ah to 0x02 to specify which BIOS call, ie read from disk 
    mov al, dh              ;Set al to the numbe of sectors 

    mov ch, 0x00            ;Start reading from cylinder 0 
    mov dh, 0x00            ;Start reading from head 0

    mov cl, 0x02            ;Start reading from second sector 

    int 0x13                ;Call BIOS to read from disk 

    jc disk_error           ;Carry flag is set by BIOS if error occured

    pop dx                  ;Return dx to original value

    cmp dh, al              ;BIOS sets al to number of sectors read 

    jne disk_error          ;If requested and read are unequal, error

    mov bx, DISK_SUCCESS    ;move to bx to prepare to print bios that we read successfully 
    call print_bios

    ret                     ;Otherwise return to callee

disk_error: 
    mov bx, DISK_ERROR      ;prepare to print_bios for error
    call print_bios
    jmp $ ;hang

DISK_ERROR db "Error reading from disk",0
DISK_SUCCESS db "Successfully read from disk",0 