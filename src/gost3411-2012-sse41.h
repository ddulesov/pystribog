
#ifndef _SSE41_H
#define _SSE41_H

#ifndef __GOST3411_HAS_SSE41__
#error "require __GOST3411_HAS_SSE41__ in config.h"
#endif

#include "gost3411-2012-precalc.h"

#include <mmintrin.h>
#include <emmintrin.h>
#include <smmintrin.h>
#include <immintrin.h>

#define XMM_EXTRACT(row,  outxmm, xmm0, xmm1, xmm2, xmm3 ) {\
    r0  = Ax[0][ _mm_extract_epi8(xmm0, row + 0)]; \
    r0 ^= Ax[1][ _mm_extract_epi8(xmm0, row + 8)]; \
    r0 ^= Ax[2][ _mm_extract_epi8(xmm1, row + 0)]; \
    r0 ^= Ax[3][ _mm_extract_epi8(xmm1, row + 8)]; \
    r0 ^= Ax[4][ _mm_extract_epi8(xmm2, row + 0)]; \
    r0 ^= Ax[5][ _mm_extract_epi8(xmm2, row + 8)]; \
    r0 ^= Ax[6][ _mm_extract_epi8(xmm3, row + 0)]; \
    r0 ^= Ax[7][ _mm_extract_epi8(xmm3, row + 8)]; \
	\
    r1  = Ax[0][ _mm_extract_epi8(xmm0, row + 1)]; \
    r1 ^= Ax[1][ _mm_extract_epi8(xmm0, row + 9)]; \
    r1 ^= Ax[2][ _mm_extract_epi8(xmm1, row + 1)]; \
    r1 ^= Ax[3][ _mm_extract_epi8(xmm1, row + 9)]; \
    r1 ^= Ax[4][ _mm_extract_epi8(xmm2, row + 1)]; \
    r1 ^= Ax[5][ _mm_extract_epi8(xmm2, row + 9)]; \
    r1 ^= Ax[6][ _mm_extract_epi8(xmm3, row + 1)]; \
    r1 ^= Ax[7][ _mm_extract_epi8(xmm3, row + 9)]; \
    \
	outxmm = _mm_set_epi64x(r1, r0); \
}

#define LPS(xmm0, xmm1, xmm2, xmm3)  { \
    __m128i tx0, tx1, tx2, tx3; \
	XMM_EXTRACT(0, tx0, xmm0, xmm1, xmm2, xmm3); \
	XMM_EXTRACT(2, tx1, xmm0, xmm1, xmm2, xmm3); \
	XMM_EXTRACT(4, tx2, xmm0, xmm1, xmm2, xmm3); \
	XMM_EXTRACT(6, tx3, xmm0, xmm1, xmm2, xmm3); \
	xmm0 = tx0; xmm1 = tx1; xmm2 = tx2; xmm3 = tx3; \
} 


#endif