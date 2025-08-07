#include "stdlib.h"
#include "idt/idt_init.h"
#include "pci/pci_init.h"
void main() {
    idt_init(); 
    pci_init(); 
    clear_screen(); 
    //vga_mem_init(); 
    print_vga("\n");
}