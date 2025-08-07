#include "idt_init.h"
#include "../stdlib.h"
#include <stdint.h>
#include <stdbool.h> 

#include "../keyboard/keyboard_scancodes.h"

static idt_entry_t idt[IDT_LENGTH];
static idtr_t idtr; 

void idt_set_descriptor(uint8_t index, void* isr, uint8_t flags) {
    idt_entry_t* descriptor       = &idt[index];

    descriptor->offset_low        = (uint32_t)isr & 0xFFFF;
    descriptor->segment_selector  = CODE_SEG;
    descriptor->flags             = flags;
    descriptor->reserved          = 0;
    descriptor->offset_high       = (uint32_t)isr >> 16;
}

__attribute__((noreturn))
void hang() {
    __asm__ volatile ("cli; hlt");
    __builtin_unreachable();  // tell compiler we never return
}

void interrupt_handler(registers_t r, uint32_t interrupt_number, stack_state_t stack_state) {

    if (interrupt_number < 32) {
        print_vga("Raised Exception Number: ");
        print_vga(itoa(interrupt_number));
        print_vga(". ");
        hang(); 
    } else if(interrupt_number == 32) {
        //This is the timer, it basically runs constantly. Not yet sure how to handle correctly
    } else if(interrupt_number == 33) {
        char keypress = scancode_to_ascii(inbyte(KEYBOARD_PORT));
        char c[2] = {keypress, '\0'};
        print_vga(c);
    } else {
        print_vga("Unhandled interrupt: ");
        print_vga(itoa(interrupt_number));
    }

    end_of_interrupt(interrupt_number); 
}

//currently just initializes the exceptions 
//all other interrupts are still unhandled
//exceptions are indices 0 - 31
void idt_init() {
    idtr.base = (uintptr_t)&idt[0];
    idtr.limit = (uint16_t)sizeof(idt_entry_t) * IDT_LENGTH - 1;

    for (uint8_t i = 0; i < 60; i++) {
        idt_set_descriptor(i, handler_address_table[i], 0x8E); //0x8e flag for exceptions 
    }

    __asm__ volatile ("lidt %0" : : "m"(idtr)); // load the new IDT

    //__asm__ volatile ("int $0x20");
    __asm__ volatile ("sti");

}