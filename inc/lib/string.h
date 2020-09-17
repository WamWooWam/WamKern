#pragma once

#ifdef __cplusplus
class String {
   public:
    static long Length(const char* str);
    static void Copy(const char* src, char* dest);
};

extern "C" {
#endif

static long strlen(const char* str);
static char* strcpy(char* dest, const char* src);

#ifdef __cplusplus
}
#endif
