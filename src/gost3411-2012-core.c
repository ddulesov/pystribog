#include "gost3411-2012-core.h"

void
GOST34112012Cleanup(GOST34112012Context *CTX)
{
    memset(CTX, 0x00, sizeof (GOST34112012Context));
}

void
GOST34112012Init(GOST34112012Context *CTX, const unsigned int digest_size)
{
    unsigned int i;
    memset(CTX, 0x00, sizeof(GOST34112012Context));
    CTX->digest_size = digest_size;
	if (digest_size == 256) {
		for (i = 0; i < 8; i++)
		{
			CTX->h.QWORD[i] = 0x0101010101010101ULL;
		}
	}
}

static inline void
pad(GOST34112012Context *CTX)
{
    if (CTX->bufsize > 63)
        return;

	memset(CTX->buffer + CTX->bufsize,
			0x00, sizeof(CTX->buffer) - CTX->bufsize);

    CTX->buffer[CTX->bufsize] = 0x01;
}

static inline  void
add512(u512_t* x, const u512_t* y)
{
#ifndef __GOST3411_BIG_ENDIAN__
    unsigned char cf = 0;
    unsigned int i;

    for (i = 0; i < 8; i++)
    {
		cf = _addcarry_u64(cf, x->QWORD[i], y->QWORD[i], &(x->QWORD[i]));
    }
#else
    const unsigned char *xp, *yp;
    unsigned char *rp;
    unsigned int i;
    int buf;

    xp = (const unsigned char *) &x[0];
    yp = (const unsigned char *) &y[0];
    rp = (unsigned char *) &r[0];

    buf = 0;
    for (i = 0; i < 64; i++)
    {
        buf = xp[i] + yp[i] + (buf >> 8);
        rp[i] = (unsigned char) buf & 0xFF;
    }
#endif
}

static inline void g(u512_t *h, const u512_t *N, const unsigned char *m) {

	__m128i xmm0, xmm1, xmm2, xmm3;
	__m128i xmm4, xmm5, xmm6, xmm7;
	register unsigned long long r0, r1;
	//key
	LOAD_XMM(h, xmm0, xmm1, xmm2, xmm3);
	
	//into_xor_m ( n )
	XOR_XMM((*N), xmm0, xmm1, xmm2, xmm3);
	
	LPS(xmm0, xmm1, xmm2, xmm3);
	//buffer
	LOADU_XMM(m, xmm4, xmm5, xmm6, xmm7);

	for (int i = 0; i < 12; i++) {
		//buffer.into_xor(key)
		XOR_XMM2(xmm4, xmm5, xmm6, xmm7, xmm0, xmm1, xmm2, xmm3);
		//buffer.lps()
		LPS(xmm4, xmm5, xmm6, xmm7);
		//key.into_xor( c[i] )
		XOR_XMM(C[i], xmm0, xmm1, xmm2, xmm3);
		//key.lps()
		LPS(xmm0, xmm1, xmm2, xmm3);
	}

	//key.xor_r( buffer )
	XOR_XMM2(xmm0, xmm1, xmm2, xmm3,  xmm4, xmm5, xmm6, xmm7 );

	//use ymm2 ymm3 as buffer is not need anymore
	LOADU_XMM(m, xmm4, xmm5, xmm6, xmm7);

	//key.xor_m ( m )
	XOR_XMM2(xmm0, xmm1, xmm2, xmm3, xmm4, xmm5, xmm6, xmm7);

	//key.xor_m ( h )
	XOR_XMM( (*h), xmm0, xmm1, xmm2, xmm3);
	STORE_XMM(h, xmm0, xmm1, xmm2, xmm3);
}

static inline void
stage2(GOST34112012Context *CTX, const unsigned char *data)
{
	g(&(CTX->h), &(CTX->N), data );
    add512(&(CTX->N), &buffer512);
    add512(&(CTX->Sigma), (const u512_t *)data);
}

static void
stage3(GOST34112012Context *CTX)
{
    ALIGNED u512_t buf = {{ 0 }};

#ifndef __GOST3411_BIG_ENDIAN__
    buf.QWORD[0] = CTX->bufsize << 3;
#else
    buf.QWORD[0] = _bswap64(CTX->bufsize << 3);
#endif

    pad(CTX);
    g(&(CTX->h), &(CTX->N), (const unsigned char *) &(CTX->buffer));

    add512(&(CTX->N), &buf);
    add512(&(CTX->Sigma), (const u512_t *) &CTX->buffer[0]);

    g(&(CTX->h), &buffer0, (const unsigned char *) &(CTX->N));
    g(&(CTX->h), &buffer0, (const unsigned char *) &(CTX->Sigma));
}

void
GOST34112012Update(GOST34112012Context *CTX, const unsigned char *data, size_t len)
{
    size_t chunksize;

    if (CTX->bufsize) {
        chunksize = 64 - CTX->bufsize;
        if (chunksize > len)
            chunksize = len;

        memcpy(&CTX->buffer[CTX->bufsize], data, chunksize);

        CTX->bufsize += chunksize;
        len -= chunksize;
        data += chunksize;
        
        if (CTX->bufsize == 64)
        {
            stage2(CTX, CTX->buffer);
            CTX->bufsize = 0;
        }
    }

    while (len > 63)
    {
        stage2(CTX, data);
        data += 64;
        len  -= 64;
    }

    if (len) {
        memcpy(&CTX->buffer, data, len);
        CTX->bufsize = len;
    }
}

void
GOST34112012Final(GOST34112012Context *CTX, unsigned char *digest)
{
    stage3(CTX);
    CTX->bufsize = 0;

    if (CTX->digest_size == 256)
        memcpy(digest, &(CTX->h.QWORD[4]), 32);
    else
        memcpy(digest, &(CTX->h.QWORD[0]), 64);
}

