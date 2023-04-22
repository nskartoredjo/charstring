#ifndef _CHAR_STRING_H_
#define _CHAR_STRING_H_

#include <stdio.h>
#include <string.h>

typedef struct {
  size_t len;
  const char *c_str;
} Literal;

typedef struct {
  const char after;
  const char until;
  const char begin;
  const char end;
} SubArgs;

#define Literal(str) \
  { .len = strlen(str), .c_str = str, }

#define String(cap)  \
  struct {           \
    size_t len;      \
    char c_str[cap]; \
    char : 8;        \
  }

#define strappf(__s, ...)                                                \
  {                                                                      \
    size_t __cap = sizeof(__s.c_str);                                    \
    __s.len +=                                                           \
        snprintf(&__s.c_str[__s.len], __cap + 1 - __s.len, __VA_ARGS__); \
    __s.len = __s.len > __cap ? __cap : __s.len;                         \
  }

#define strsub(__s, __o, ...)                                                  \
  {                                                                            \
    SubArgs __a = {__VA_ARGS__};                                               \
    char *__paft = strchr(__o.c_str, __a.after | __a.begin);                   \
    if (__paft) {                                                              \
      char *__psub = __paft + (__a.after ? 1 : 0);                             \
      char *__punt = strchr(__paft + 1, __a.until | __a.end);                  \
      __punt =                                                                 \
          __punt ? __punt + (__a.end ? 1 : 0) : &__o.c_str[sizeof(__o.c_str)]; \
      __s.len = __punt - __psub;                                               \
      size_t __cap = sizeof(__s.c_str);                                        \
      __s.len = __s.len > __cap ? __cap : __s.len;                             \
      strncpy(__s.c_str, __psub, __s.len);                                     \
    }                                                                          \
  }

#endif /* _CHAR_STRING_H_ */