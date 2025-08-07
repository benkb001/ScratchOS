#include "../stdlib.h"

static void* next_available = HEAPSTART; 

void* kmalloc(int size) {
    void* temp = next_available; 
    if(next_available + size < HEAPEND) {
        next_available += size; 
        return next_available; 
    } else {
        print_vga("Heap Full");
        return (void*) HEAPSTART; 
    }
}