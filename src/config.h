#pragma once

#include <immintrin.h>
//#define __GOST3411_HAS_SSE41__
//#define __GOST3411_HAS_SSE2__

#if defined _MSC_VER
#define ALIGN(x) __declspec(align(x))
#define ALIGNED  __declspec(align(16)) 
#else
#define ALIGN(x) __attribute__ ((__aligned__(x)))
#define ALIGNED __attribute__  ((__aligned__(16)))
#endif

typedef unsigned __int64  uint64;

typedef ALIGNED union u512
{
	unsigned long long QWORD[8];
} u512_t;

#ifdef _DEBUG 
void debug_buf(const char* prefix, unsigned char *buf, size_t buflen);
void debug_xmm(const char* prefix, __m128i* x0, __m128i* x1, __m128i* x2, __m128i* x3);
#endif