#ifndef KMALLOCH 
#define KMALLOCH 
    #define HEAPSTART 0x400000
    #define HEAPEND   0x800000 
    void* kmalloc(int size); 
#endif 