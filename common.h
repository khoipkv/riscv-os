#pragma once

#define va_list  __builtin_va_list
#define va_start __builtin_va_start
#define va_end   __builtin_va_end
#define va_arg   __builtin_va_arg

#define PAGE_SIZE 4096

#define true 1
#define false 0
#define NULL ((void *) 0)
#define align_up(value, align)   __builtin_align_up(value, align)
#define is_aligned(value, align) __builtin_is_aligned(value, align)
#define offsetof(type, member)   __bultin_offsetof(type, member)


#define PANIC(fmt, ...)                                                         \
    do {                                                                        \
        printf("PANIC: %s:%d: " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__);   \
        while (1) {}                                                            \
    } while (0)                                                                 \


typedef int bool;
typedef int errno_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;
typedef uint8_t size_t;
typedef uint32_t paddr_t;
typedef uint32_t vaddr_t;
typedef size_t rsize_t;

void printf(const char *fmt, ...);
void *memset(void *buf, char c, size_t n);
void *memcpy(void *dst, const void *src, size_t n);
int strcmp(const char *s1, const char *s2);

char *strcpy(char *dst, const char *src);

// TODO: Add-ons
errno_t strcpy_s(char* restrict dest, rsize_t destsz, const char* restrict src);

size_t strlen( const char* str );
size_t strnlen_s( const char* str, size_t strsz );
