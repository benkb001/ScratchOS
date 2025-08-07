#include "pci_init.h"
#include "../stdlib.h"

void pci_init() {
    //tell pic 1 and 2 that we are doing the initializing sequence
    outbyte(PIC1_COMMAND, PIC_ICW1_INIT);
    outbyte(PIC2_COMMAND, PIC_ICW1_INIT);

    //Next 3 Commands are vector offset, wiring info, and environment info 

    //First, tell them which offsets we want, ie where in the IDT should interrupts be mapped to
    outbyte(PIC1_DATA, PIC1_ICW2_OFFSET);
    outbyte(PIC2_DATA, PIC2_ICW2_OFFSET);

    //Second, tell slave and master they are connected by IRQ 2 
    outbyte(PIC1_DATA, PIC1_ICW3_SLAVELINE);
    outbyte(PIC2_DATA, PIC2_ICW3_MASTERLINE);
    //Finally, tell them we are on 8086 instead of 8080
    outbyte(PIC1_DATA, ICW4_8086);
    outbyte(PIC2_DATA, ICW4_8086);

    //Fully unmask both pic 
	outbyte(PIC1_DATA, 0);
	outbyte(PIC2_DATA, 0);
}