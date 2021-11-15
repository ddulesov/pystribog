#pragma once

#include <immintrin.h>
#include <string.h>
#if defined(__GNUC__)
#include <x86intrin.h>
#endif

#if defined _MSC_VER
#define ALIGN(x) __declspec(align(x))
#define ALIGNED  __declspec(align(16)) 
#else
#define ALIGN(x) __attribute__ ((__aligned__(x)))
#define ALIGNED __attribute__  ((__aligned__(16)))
#endif

typedef ALIGNED union u512
{
    unsigned long long QWORD[8];
} u512_t;

#ifdef _DEBUG 
void debug_buf(const char* prefix, unsigned char *buf, size_t buflen);
void debug_xmm(const char* prefix, __m128i* x0, __m128i* x1, __m128i* x2, __m128i* x3);
#endif