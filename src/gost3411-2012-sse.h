#pragma once

#ifndef _SSE_H
#define _SSE_H

#include <mmintrin.h>
#include <emmintrin.h>
#include <smmintrin.h>
#include <immintrin.h>

#define STORE_XMM(M, xmm0, xmm1, xmm2, xmm3 ) \
    _mm_store_si128((__m128i *) &(M->QWORD[0]), xmm0 ); \
    _mm_store_si128((__m128i *) &(M->QWORD[2]), xmm1 ); \
    _mm_store_si128((__m128i *) &(M->QWORD[4]), xmm2 ); \
    _mm_store_si128((__m128i *) &(M->QWORD[6]), xmm3 ); 

#define LOAD_XMM(MP, xmm0, xmm1, xmm2, xmm3) \
    xmm0 = _mm_load_si128((const __m128i *) &(MP->QWORD[0])); \
    xmm1 = _mm_load_si128((const __m128i *) &(MP->QWORD[2])); \
    xmm2 = _mm_load_si128((const __m128i *) &(MP->QWORD[4])); \
    xmm3 = _mm_load_si128((const __m128i *) &(MP->QWORD[6])); 

#define LOADU_XMM(M, xmm0, xmm1, xmm2, xmm3) \
    xmm0 = _mm_loadu_si128((const __m128i *) (M   )); \
    xmm1 = _mm_loadu_si128((const __m128i *) (M+16)); \
    xmm2 = _mm_loadu_si128((const __m128i *) (M+32)); \
    xmm3 = _mm_loadu_si128((const __m128i *) (M+48)) ; 

#define XOR_XMM(MP, xmm0, xmm1, xmm2, xmm3) { \
    xmm0 = _mm_xor_si128(xmm0, _mm_load_si128((const __m128i *)  &(MP.QWORD[0])));\
    xmm1 = _mm_xor_si128(xmm1, _mm_load_si128((const __m128i *)  &(MP.QWORD[2])));\
    xmm2 = _mm_xor_si128(xmm2, _mm_load_si128((const __m128i *)  &(MP.QWORD[4])));\
    xmm3 = _mm_xor_si128(xmm3, _mm_load_si128((const __m128i *)  &(MP.QWORD[6])));\
}

#define XOR_XMM2( xmm0, xmm1, xmm2, xmm3, xmm4, xmm5, xmm6, xmm7) \
    xmm0 = _mm_xor_si128(xmm0, xmm4); \
    xmm1 = _mm_xor_si128(xmm1, xmm5); \
    xmm2 = _mm_xor_si128(xmm2, xmm6); \
    xmm3 = _mm_xor_si128(xmm3, xmm7); \



#endif