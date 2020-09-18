#pragma once
#include <stdint.h>
#include <stddef.h>
#include <snprintf/snprintf.h>

#ifdef __cplusplus
class String {
   public:
    static size_t Length(const char* str);
    static void Copy(const char* src, char* dest);
};

extern "C" {
#endif

static size_t strlen(const char* str);
static char* strcpy(char* dest, const char* src);

#ifdef __cplusplus
}
#endif
