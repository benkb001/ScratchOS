#ifndef PCI_INITH
#define PCI_INITH
#define PIC1		0x20		      // IO base address for master PIC
#define PIC2		0xA0		      // IO base address for slave PIC
#define PIC1_COMMAND	PIC1
#define PIC1_DATA	(PIC1+1)
#define PIC2_COMMAND	PIC2
#define PIC2_DATA	(PIC2+1)

#define PIC_EOI     0x20              //End of Interrupt instruction 



#define PIC_ICW1_INIT 0x11            //First code sent, says we are initializing the PIC 

#define PIC1_ICW2_OFFSET 0x20         //because this is the first address that is not already taken by exceptions 
#define PIC2_ICW2_OFFSET 0x28

//First one tells master where slave is, second tells slave where master is 

#define PIC1_ICW3_SLAVELINE 0x04     //In binary, this is bit 2 set, because slave is connected at IRQ 2 
#define PIC2_ICW3_MASTERLINE 0x02    //This one is interpreted as decimal, so 2 implies IRQ 2

#define ICW4_8086	0x01             //tell the PIC we are in 16 bit addressing (8086, not 8080)

void pci_init(void); 
#endif 