#include <stdbool.h> 

char* strcat(char *dest, const char *src) {
    char *ptr = dest; // Keep track of the original destination
    
    // Move the pointer to the end of the destination string
    while (*ptr != '\0') {
        ptr++;
    }
    
    // Copy the source string to the end of the destination string
    while (*src != '\0') {
        *ptr = *src;
        ptr++;
        src++;
    }
    
    // Add the null terminator at the end of the concatenated string
    *ptr = '\0';
    
    // Return the original destination pointer
    return dest;
}

void reverse(char str[], int length) {
    int start = 0;
    int end = length - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        end--;
        start++;
    }
}

char* itoa_help(int num, char* str, int base) {
    int i = 0;
    bool isNegative = false;

    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    if (num < 0 && base == 10) {
        isNegative = true;
        num = -num;
    }

    while (num != 0) {
        int rem = num % base;
        str[i++] = (rem > 9) ? (rem - 10) + 'A' : rem + '0';
        num = num / base;
    }

    if (isNegative) {
        str[i++] = '-';
    }

    str[i] = '\0';
    reverse(str, i);
    return str;
}

char* itoa(int num) {
    return itoa_help(num, "", 10);
}

int length(char* str) {
    int i = 0; 
    while(str[i] != '\0') {
        i++; 
    }
    return i; 
}