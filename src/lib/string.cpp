#include "lib/string.h"

extern "C" {
size_t strlen(const char* str) {
    const char* temp;
    for (temp = str; *temp != '\0'; ++temp)
        ;  // loop

    return temp - str;
}

char* strcpy(char* dest, const char* src) {
    char* temp = dest;
    while ((*dest++ = *src++) != '\0')
        ;  // loop

    return temp;
}

int strcmp(const char* left, const char* right) {
    while (*left) {
        if (*left != *right) break;
        left++;
        right++;
    }

    return *(unsigned char*)left - *(unsigned char*)right;
}

char* strcat(char* dest, const char* source) {
    strcpy(dest + strlen(dest), source);
    return dest;
}
}

size_t String::Length(const char* str) {
    return strlen(str);
}

void String::Copy(const char* src, char* dest) {
    strcpy(dest, src);
}