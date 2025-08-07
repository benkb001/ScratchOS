

[org 0x7c00]            ; says that we expect the program to be running at 0x7c00, will automatically add to addresses 
KERNEL_OFFSET equ 0x1000 ;Memory offset from which we will load the kernel 

mov [BOOT_DRIVE], dl    ;Store the boot drive value, BIOS puts this in dl, we need to remember it to later load kernel from it 

mov bp, 0x9000          ; set the stack pointer and base pointer 
mov sp, bp 

mov bx, MSG_REAL_MODE
call print_bios

call load_kernel        ;Load our kernel before swithcing into protected because we need access to BIOS still 

call switch_to_pm       ; Note that we don't 'return' back from here, this call will switch execution to begin_pm below

jmp $                   ; This shouldn't run 

%include "boot/print_bios.asm" 
%include "boot/disk_load.asm" 
%include "boot/global_descriptor_table.asm" 
%include "boot/print.asm" 
%include "boot/switch_to_pm.asm" 

[bits 16]

load_kernel: 
    mov bx, MSG_LOAD_KERNEL 
    call print_bios 

    mov dh, 0x0f        ; These 3 lines prepare for disk load, say to load 
                        ;15 sectors into memory, from the original drive at offset of where kernel should be 
    mov ax, 0x0000
    mov es, ax

    mov dl, [BOOT_DRIVE]
    mov bx, KERNEL_OFFSET
    
    call disk_load 

    ret

[bits 32]               ; we are now in 32 bit mode, after calling switch_to_pm ! 

BEGIN_PM: 
    mov ebx, MSG_PROTECTED ;Print success moving into protected mode
    call print

    call KERNEL_OFFSET
    
    jmp $ ;hang

BOOT_DRIVE db 0
MSG_PROTECTED db "S Landed in protected mode, testing",0 
MSG_LOAD_KERNEL db "Started to load kernel",0
MSG_REAL_MODE db "Began in 16 bit real mode",0 

times 510 - ($ - $$) db 0 ; 0 padding 
dw 0xaa55               ; magic number, so hardware knows this is the bootstrap section