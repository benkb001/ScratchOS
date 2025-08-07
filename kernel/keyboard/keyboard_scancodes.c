#include <stdint.h>

char scancode_to_ascii(uint8_t code) {
    switch (code) {
        case 2: return '1';
        case 3: return '2';
        case 4: return '3';
        case 5: return '4';
        case 6: return '5';
        case 7: return '6';
        case 8: return '7';
        case 9: return '8';
        case 10: return '9';
        case 11: return '0';
        case 12: return '-';
        case 13: return '=';
        case 14: return '\b'; // Backspace
        case 15: return '\t'; // Tab
        case 16: return 'Q';
        case 17: return 'W';
        case 18: return 'E';
        case 19: return 'R';
        case 20: return 'T';
        case 21: return 'Y';
        case 22: return 'U';
        case 23: return 'I';
        case 24: return 'O';
        case 25: return 'P';
        case 26: return '[';
        case 27: return ']';
        case 28: return '\n'; // Enter
        case 30: return 'A';
        case 31: return 'S';
        case 32: return 'D';
        case 33: return 'F';
        case 34: return 'G';
        case 35: return 'H';
        case 36: return 'J';
        case 37: return 'K';
        case 38: return 'L';
        case 39: return ';';
        case 40: return '\'';
        case 41: return '`';
        case 44: return 'Z';
        case 45: return 'X';
        case 46: return 'C';
        case 47: return 'V';
        case 48: return 'B';
        case 49: return 'N';
        case 50: return 'M';
        case 51: return ',';
        case 52: return '.';
        case 53: return '/';
        case 57: return ' '; // Spacebar
        default: return '\0';   // Unknown or non-printable key
    }
}