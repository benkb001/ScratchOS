[extern interrupt_handler]

common_interrupt_handler: 
    pushad                                  ; push all registers to the stack 
    cld                                     ; clear direction flag
    call interrupt_handler                  ; call the c function 
    popad                                   ; return all registers to previous state
    add esp, 8                             ; return stack to previous state 
    iret                                    ; go back to code before interrupt 

%macro no_error_code_interrupt_handler 1
global interrupt_handler_%1
interrupt_handler_%1: 
    push dword 0                            ; push 0 for the error code 
    push dword %1                           ; push the interrupt number 
    jmp common_interrupt_handler
%endmacro

%macro error_code_interrupt_handler 1
global interrupt_handler_%1
interrupt_handler_%1: 
    ;don't need to push an error code because the cpu already did that 
    push dword %1                           ; push the interrupt number 
    jmp common_interrupt_handler
%endmacro    

; initialize addresses for all interrupt numbers 

error_code_interrupt_handler 0
no_error_code_interrupt_handler 1
no_error_code_interrupt_handler 2
no_error_code_interrupt_handler 3
no_error_code_interrupt_handler 4
no_error_code_interrupt_handler 5
no_error_code_interrupt_handler 6
no_error_code_interrupt_handler 7
error_code_interrupt_handler    8
no_error_code_interrupt_handler 9
error_code_interrupt_handler    10
error_code_interrupt_handler    11
error_code_interrupt_handler    12
error_code_interrupt_handler    13
error_code_interrupt_handler    14
no_error_code_interrupt_handler 15
no_error_code_interrupt_handler 16
error_code_interrupt_handler    17
no_error_code_interrupt_handler 18
no_error_code_interrupt_handler 19
no_error_code_interrupt_handler 20
no_error_code_interrupt_handler 21
no_error_code_interrupt_handler 22
no_error_code_interrupt_handler 23
no_error_code_interrupt_handler 24
no_error_code_interrupt_handler 25
no_error_code_interrupt_handler 26
no_error_code_interrupt_handler 27
no_error_code_interrupt_handler 28
no_error_code_interrupt_handler 29
error_code_interrupt_handler    30
no_error_code_interrupt_handler 31


%assign i 32
%rep 30 
    no_error_code_interrupt_handler i
%assign i i+1
%endrep

global handler_address_table
handler_address_table: 
    %assign i 0 
    %rep 60
        dd interrupt_handler_%+i
    %assign i i+1 
    %endrep
