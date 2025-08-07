#include "port_io.h"
#include <stdint.h>
//Read one byte to the specified port
void outbyte(unsigned short port, unsigned char val) {
    //outb %0, %1 reads the value 0 into the port specificed at 1 
    // : : means the following are input operands
    //"a"(val) puts val into the ax register, next puts port into dx register 
    //Because there are no output, both refer to the input specifications
    __asm__ volatile("outb %0, %1" : : "a"(val), "d"(port));
}

//Read one byte from the specified port 
unsigned char inbyte(unsigned short port) {
    unsigned char result; 
    //inb r1, r2 reads the value in port r2 into r1 
    //%0 goes to the first output spec, =a
    //%1 goes to the first input spec, d(port)
    __asm__ volatile("inb %1, %0" : "=a"(result) : "d"(port));
    return result; 
}

#define PIC1		0x20		/* IO base address for master PIC */
#define PIC2		0xA0		/* IO base address for slave PIC */
#define PIC1_COMMAND	PIC1
#define PIC2_COMMAND	PIC2
#define PIC_EOI     0x20        //End of Interrupt instruction

void end_of_interrupt(uint32_t interrupt_number) {
    if(interrupt_number >= 40) {
        //PIC2_COMMAND is slave, only tell it if needed, ie if interrupt num is ge 40 we know it came from slave
        //So also tell slave eoi 
            outbyte(PIC2_COMMAND, PIC_EOI);
        }
        outbyte(PIC1_COMMAND, PIC_EOI);
    }