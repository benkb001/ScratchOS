section .text
global _start
_start:

[bits 32]       ;32 bits because we are in pm by this point 
[extern main]   ;So linker knows a function called main exists 
call main       ;So we enter into main 
jmp $           ;hang

section .note.GNU-stack noalloc noexec nowrite