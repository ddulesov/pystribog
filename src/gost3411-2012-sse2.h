#pragma once
#ifndef _SSE2_H
#define _SSE2_H

#ifndef __GOST3411_HAS_SSE2__
#error "require __GOST3411_HAS_SSE2__ in config.h"
#endif

#include "gost3411-2012-precalc.h"

#include <mmintrin.h>
#include <emmintrin.h>
#include <smmintrin.h>
#include <immintrin.h>

#define LO(v) (unsigned char)(v)
#define HI(v) (unsigned char)((v) >> 8 )

#define XMM_EXTRACT(row,  outxmm, xmm0, xmm1, xmm2, xmm3 ) {\
    register int ax; \
    ax = _mm_extract_epi16(xmm0, row + 0); \
    r0  = Ax[0][LO(ax)]; \
    r1  = Ax[0][HI(ax)]; \
    \
    ax =  _mm_extract_epi16(xmm0, row + 4); \
    r0 ^= Ax[1][LO(ax)]; \
    r1 ^= Ax[1][HI(ax)]; \
    \
    ax =  _mm_extract_epi16(xmm1, row + 0); \
    r0 ^= Ax[2][LO(ax)]; \
    r1 ^= Ax[2][HI(ax)]; \
    \
    ax =  _mm_extract_epi16(xmm1, row + 4); \
    r0 ^= Ax[3][LO(ax)]; \
    r1 ^= Ax[3][HI(ax)]; \
    \
    ax =  _mm_extract_epi16(xmm2, row + 0); \
    r0 ^= Ax[4][LO(ax)]; \
    r1 ^= Ax[4][HI(ax)]; \
    \
    ax =  _mm_extract_epi16(xmm2, row + 4); \
    r0 ^= Ax[5][LO(ax)]; \
    r1 ^= Ax[5][HI(ax)]; \
    \
    ax =  _mm_extract_epi16(xmm3, row + 0); \
    r0 ^= Ax[6][LO(ax)]; \
    r1 ^= Ax[6][HI(ax)]; \
    \
    ax =  _mm_extract_epi16(xmm3, row + 4); \
    r0 ^= Ax[7][LO(ax)]; \
    r1 ^= Ax[7][HI(ax)]; \
    \
    outxmm = _mm_set_epi64x(r1, r0); \
}

#define LPS(xmm0, xmm1, xmm2, xmm3)  { \
    __m128i tx0, tx1, tx2, tx3; \
    XMM_EXTRACT(0, tx0, xmm0, xmm1, xmm2, xmm3); \
    XMM_EXTRACT(1, tx1, xmm0, xmm1, xmm2, xmm3); \
    XMM_EXTRACT(2, tx2, xmm0, xmm1, xmm2, xmm3); \
    XMM_EXTRACT(3, tx3, xmm0, xmm1, xmm2, xmm3); \
    xmm0 = tx0; xmm1 = tx1; xmm2 = tx2; xmm3 = tx3; \
} 

#endif