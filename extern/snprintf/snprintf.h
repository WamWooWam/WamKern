#pragma once
#include <stdarg.h>
#include <stddef.h>

#define HAVE_STDARG_H 1
#define HAVE_STDDEF_H 1
#define HAVE_FLOAT_H 1
#define HAVE_STDLIB_H 1
#define HAVE_VA_COPY 1

#ifdef __cplusplus
extern "C" {
#endif

#ifdef TEST
#define malloc dlmalloc
#endif

int rpl_vsnprintf(char *, size_t, const char *, va_list);
int rpl_snprintf(char *, size_t, const char *, ...);
int rpl_vasprintf(char **, const char *, va_list);
int rpl_asprintf(char **, const char *, ...);

#define vsnprintf rpl_vsnprintf
#define snprintf rpl_snprintf
#define vasprintf rpl_vasprintf
#define asprintf rpl_asprintf

#ifdef __cplusplus
}
#endif