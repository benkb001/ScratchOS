#include "../stdlib.h"
#include <stdint.h>
#include <stdbool.h> 

//Returns the cursor position, this is a value from 0 to 1999 (rows * cols)
unsigned short get_cursor() {
    //this tells the command port that we are talking about cursor high byte in the next call to it
    outbyte(COMMAND_PORT, CURSOR_HIGH_BYTE);
    //this takes in the cursor high byte from the port
    unsigned char high = inbyte(DATA_PORT); 
    //this does the same for low byte
    outbyte(COMMAND_PORT, CURSOR_LOW_BYTE);
    unsigned char low = inbyte(DATA_PORT); 
    //this combines the two values into a short
    return ((unsigned short)high << 8 | low);
}

int get_cursor_row() {
    return get_cursor() / MAX_COLS; 
}

int get_cursor_column() {
    return get_cursor() % MAX_COLS; 
}

//Sets the cursor index to the specified index. Because unsigned never negative
//If too large, puts it in the last spot
void set_cursor_index(unsigned short index) {
    if(index >= VIDEO_MEM_SIZE) {
        index = VIDEO_MEM_SIZE - 1; 
    }
   
    //Get high and low bytes
    unsigned char high = index >> 8; 
    unsigned char low = index & 0xff;
    //Tell the command port we are referring to cursor high byte in next call to data port
    outbyte(COMMAND_PORT, CURSOR_HIGH_BYTE); 
    //Assign our high byte to the cursor high byte
    outbyte(DATA_PORT, high); 
    //Same with low byte 
    outbyte(COMMAND_PORT, CURSOR_LOW_BYTE); 
    outbyte(DATA_PORT, low);
}

//Sets the cursor to a specific row/column position 
void set_cursor(int row, int col) {
    unsigned short index = (unsigned short) (row * MAX_COLS + col);
    set_cursor_index(index); 
}

//Checks that an address is within the start and end specs
bool in_range(int start, int end, char* addr) {
    if(( (uintptr_t)addr >= (uintptr_t)start) && 
       ( (uintptr_t)addr < (uintptr_t)end)  ) {
        return true; 
      } else {
        return false; 
      }
}

bool is_code(char code) {
    if( code == '\b' || code == '\n' || code == '\t') {
        return true; 
    }
    return false; 
}

void print_vga_code(char code, char** video_memory, int* cursor_pos, int* row, int* column) {
    if(code == '\b' && (*cursor_pos % 80 > COMMAND_PROMPT_LENGTH)) {
        *video_memory -= 2; 
        **video_memory = ' ';
        **(video_memory + 1) = 0x0f; 
        *video_memory -= 2; 
        *cursor_pos -= 1; 
    } else if(code == '\t') {
        for(int i = 0; i < 4; i++) {
            **video_memory = ' ';
            **(video_memory + 1) = 0x0f; 
            *video_memory += 2; 
            *cursor_pos += 1; 
        }
    } else if(code == '\n') {
        int row = min(MAX_ROWS - 1, get_cursor_row() + 1); 
        if(row == MAX_ROWS - 1) {
            vga_new_row(); 
        }
        set_cursor(row, 0);
        print_vga(COMMAND_PROMPT);
        *cursor_pos = get_cursor();
        video_memory = (VIDEO_MEM_BASE + 2 * (*cursor_pos)); 
    }
}

//Print the string to the current cursor position 
void print_vga(char* string) {
    //First get current cursor position 
    int cursor_pos = get_cursor();
    int row = get_cursor_row(); 
    int column = get_cursor_column(); 
    //Get the current address to print to based on cursor position 
    char* video_memory = (char*) (VIDEO_MEM_BASE + 2 * get_cursor());
    int cur = 0; 

    while(string[cur] != '\0') {

        if(cursor_pos >= VIDEO_MEM_SIZE - 1) {
            vga_new_row(); 
            cursor_pos = (MAX_COLS * (MAX_ROWS - 1)); 
            video_memory = 2 * (VIDEO_MEM_END - MAX_COLS);
        } 

        if(is_code(string[cur])) {
            print_vga_code(string[cur], &video_memory, &cursor_pos, &row, &column);
        } else {
            //Set the current position in VGA to the current character
            *video_memory = string[cur];
            //Set the current font position in VGA to white on black 
            *(video_memory + 1) = 0x0f;
            //Increment address so we write to the correct next location in memory
            video_memory += 2; 
            //Increment cursor position so we write to the correct next cursor position 
            cursor_pos++; 
        }

        cur++; 
    }
    
    //Update the cursor position to be write after the last character written 
    set_cursor_index(cursor_pos); 
}

//Clears the screen, inefficient currently but whatever.
//Will need to adjust once scrolling is implimented potentially?  
void clear_screen() {
    set_cursor(0, 0); 
    for(int i = 0; i < VIDEO_MEM_SIZE; i++) {
        print_vga(" ");
    }
    set_cursor(0, 0);
}

void vga_new_row() {
    //so it starts at row 1 instead of row 0 
    char* video_memory = (char*) (VIDEO_MEM_BASE);
    for(int i = 0; i < 2 * (VIDEO_MEM_SIZE - MAX_COLS); i += 2) {
        video_memory[i] = video_memory[i + (2 * MAX_COLS)];
    }   
    
    for(int i = 2 * (VIDEO_MEM_SIZE - MAX_COLS); i < 2 * VIDEO_MEM_SIZE; i+= 2) {
        video_memory[i] = ' ';
    }
}