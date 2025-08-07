#include <stdint.h>
#include <stdbool.h> 

#ifndef IDT_INITH
#define IDT_INITH

#define CODE_SEG 8 
#define IDT_LENGTH 256

typedef struct __attribute__((packed)) registers_t {
    uint32_t r1; 
    uint32_t r2; 
    uint32_t r3; 
    uint32_t r4;
    uint32_t r5;
    uint32_t r6;
    uint32_t r7;
    uint32_t r8;
} registers_t;

typedef struct __attribute__((packed)) stack_state_t {
        uint32_t error_code;
        uint32_t eip;
        uint32_t cs;
        uint32_t eflags;
} stack_state_t;

typedef struct __attribute__((packed)) idt_entry_t {
    uint16_t offset_low;
    uint16_t segment_selector; 
    uint8_t reserved; 
    uint8_t flags; 
    uint16_t offset_high; 
} idt_entry_t;

typedef struct __attribute__((packed)) idtr_t {
	uint16_t	limit;
	uint32_t	base;
} idtr_t;

extern void* handler_address_table[];

void interrupt_handler(registers_t r, uint32_t interrupt_number, stack_state_t stack_state);
void idt_set_descriptor(uint8_t index, void* isr, uint8_t flags);
void idt_init(void);

__attribute__((noreturn))
void exception_handler(void);


#endif 