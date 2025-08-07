#ifndef PORT_IOH
#define PORT_IOH

#include <stdint.h>

#define KEYBOARD_PORT 0x60
    void outbyte(unsigned short port, unsigned char val);
    unsigned char inbyte(unsigned short port);
    void end_of_interrupt(uint32_t interrupt_number);
#endif