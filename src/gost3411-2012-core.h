#pragma once
#ifndef _CORE_H
#define _CORE_H

#include "config.h"
#include "gost3411-2012-sse.h"

#if defined   __GOST3411_HAS_SSE41__
#include "gost3411-2012-sse41.h"
#elif defined __GOST3411_HAS_SSE2__
#include "gost3411-2012-sse2.h"
#else
#error "for configuration set env variables or edit config.h"
#endif

#include "gost3411-2012-const.h"
#include "gost3411-2012-precalc.h"

ALIGNED typedef struct GOST34112012Context
{
    ALIGNED unsigned char buffer[64];
    ALIGNED u512_t h;
    ALIGNED u512_t N;
    ALIGNED u512_t Sigma;
    size_t  bufsize;
    unsigned int digest_size;
} GOST34112012Context;

void GOST34112012Init(GOST34112012Context *CTX, const unsigned int digest_size);

void GOST34112012Update(GOST34112012Context *CTX, const unsigned char *data, size_t len); 

void GOST34112012Final(GOST34112012Context *CTX, unsigned char *digest); 

void GOST34112012Cleanup(GOST34112012Context *CTX);

#endif
