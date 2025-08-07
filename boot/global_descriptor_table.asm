gdt_start:          ;represents start of gdt

gdt_null:           ;You must define some 0s at the beginning for the first segment in the GDT 
    dd 0x0           ;If a program attempts to access this by leading 0 before address
    dd 0x0           ;It will be invalid (just read all 0s)

gdt_code:           ;for the first section, this represents code 
    
    dw 0xffff       ;this sets the first 16 bits to 1 representing max limit 
    
    dw 0x0           ;this sets the next 16 bits to 0 representing the section starts at address 0 
    
    db 0x0           ;sets the next 8 bits to same 
    
    db 10011010b    ;next two set flags 
                    ;First 4 bytes are 1001 
                    ;1, says this segment is present and can be accessed 
                    ;00, gives highest privelege to the segment, because this is for the kernel ^^
                    ;1, says this is code/data, not system 
                    ;the last 4 bits here, 1010
                    ;First 1 says this is code, not data 
                    ;Next, 0, says not conforming, ie code with lower privelege can't call this segment
                    ;Next, 1, says Readable, so we can read constants defined here 
                    ;Next, 0, says it hasn't been accessed yet, so we can check here if the cpu ever accesses this for debugging
    
    db 11001111b    ;First 4 bytes are 1100, flags
                    ;First, 1, says 4kb granularity, ie multiply limit by 4096 
                    ;Next, 1, says this is 32 bit 
                    ;Next, 0, says NOT 64 bit 
                    ;Next, 0, is just ignored by the CPU, but can be used by us the OS 
                    ;Second 4 bytes, 1111, are for the limit 
    
    db 0x0          ;Define last byte, base, to 0 
    
gdt_data:           ;All same, EXCEPT 5th byte bit 3!!!
    dw 0xffff
    dw 0x0
    db 0x0 
    db 10010010b    ;The bit change here is to reflect this is data, not code ! ! ! 
    db 11001111b 
    db 0x0

gdt_end:            ;Used in const calculations below

gdt_descriptor: 
    dw gdt_end - gdt_start - 1 ; basically the machine expects first the size of the gdt, then the start address of it 
    dd gdt_start               ; double because 32 bit addreseses now 

CODE_SEG equ gdt_code - gdt_start ; This is just the start address of the segment for code in the GDT, can be accessed to jump to the code segment
DATA_SEG equ gdt_data - gdt_start ; This is same for data 