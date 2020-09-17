#include "lib/string.h"

extern "C" {
static long strlen(const char* str) {
    const char* temp;
    for (temp = str; *temp != '\0'; ++temp)
        ;  // loop

    return temp - str;
}

static char* strcpy(char* dest, const char* src) {
    char* temp = dest;
    while ((*dest++ = *src++) != '\0')
        ;  // loop

    return temp;
}
}

long String::Length(const char* str) {
    return strlen(str);
}

void String::Copy(const char* src, char* dest) {
    strcpy(dest, src);
}