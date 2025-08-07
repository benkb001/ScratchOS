#ifndef PRINT_H
#define PRINT_H

#define VIDEO_MEM_BASE 0xb8000
#define VIDEO_MEM_END 0xb8fa0 
#define VIDEO_MEM_SIZE 2000
#define MAX_COLS 80 
#define MAX_ROWS 25
#define COMMAND_PORT 0x3d4
#define DATA_PORT 0x3d5
#define CURSOR_HIGH_BYTE 0x0e
#define CURSOR_LOW_BYTE 0x0f
#define COMMAND_PROMPT "User> "
#define COMMAND_PROMPT_LENGTH 6

void print_vga(char *string);
void set_cursor(int row, int col);
void clear_screen(void); 
void vga_mem_init(void); 

typedef struct vga_mem_t {
    char text[1024][80];
    int row;
} vga_mem_t; 

#endif