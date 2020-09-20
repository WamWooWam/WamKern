#pragma once
#include <snprintf/snprintf.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
class String {
   public:
    static size_t Length(const char* str);
    static void Copy(const char* src, char* dest);
};

extern "C" {
#endif

char* strcpy(char* s1, const char* s2);
char* strncpy(char* s1, const char* s2, size_t n);
char* strcat(char* s1, const char* s2);
char* strncat(char* s1, const char* s2, size_t n);
int strcmp(const char* s1, const char* s2);
int strncmp(const char* s1, const char* s2, size_t n);
int strcoll(const char* s1, const char* s2);
size_t strxfrm(char* s1, const char* s2, size_t n);
const char* strchr(const char* s, int c);
size_t strcspn(const char* s1, const char* s2);
const char* strpbrk(const char* s1, const char* s2);
const char* strrchr(const char* s, int c);
size_t strspn(const char* s1, const char* s2);
const char* strstr(const char* s1, const char* s2);
char* strtok(char* s1, const char* s2);
char* strerror(int errnum);
size_t strlen(const char* s);

double strtod (const char* str, char** endptr);
long int strtol (const char* str, char** endptr, int base);
long long int strtoll (const char* str, char** endptr, int base);

#ifdef __cplusplus
}
#endif
