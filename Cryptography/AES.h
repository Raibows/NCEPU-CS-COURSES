#pragma once
typedef unsigned char   u1byte;
typedef unsigned short  u2byte;
typedef unsigned long   u4byte;

typedef signed char     s1byte;
typedef signed short    s2byte;
typedef signed long     s4byte;
#define	LITTLE_ENDIAN
#ifdef _MSC_VER

#  include <stdlib.h>
#include <string>

#  pragma intrinsic(_lrotr,_lrotl)
#  define rotr(x,n) _lrotr(x,n)
#  define rotl(x,n) _lrotl(x,n)

#else

#define rotr(x,n)   (((x) >> ((int)(n))) | ((x) << (32 - (int)(n))))
#define rotl(x,n)   (((x) << ((int)(n))) | ((x) >> (32 - (int)(n))))

#endif

/* Invert byte order in a 32 bit variable                           */

#define bswap(x)    (rotl(x, 8) & 0x00ff00ff | rotr(x, 8) & 0xff00ff00)

/* Extract byte from a 32 bit quantity (little endian notation)     */

#define byte(x,n)   ((u1byte)((x) >> (8 * n)))

/* Input or output a 32 bit word in machine order					*/

#ifdef	LITTLE_ENDIAN

#define	u4byte_in(x)		(*(u4byte*)(x))
#define	u4byte_out(x, v)	(*(u4byte*)(x) = (v)) 

#else

#define	u4byte_in(x)		bswap(*(u4byte)(x))
#define	u4byte_out(x, v)	(*(u4byte*)(x) = bswap(v)) 

#endif

class AES
{
private:
	u4byte  k_len;
	u4byte  e_key[64];
	u4byte  d_key[64];
public:
	void set_key(const u1byte key[], const u4byte key_bits);
	void encrypt(const u1byte in_blk[16], u1byte out_blk[16]);
	void decrypt(const u1byte in_blk[16], u1byte out_blk[16]);
	void tianchong(unsigned char* c, long length);
	long untianchong(unsigned char* c, long length);
	void encryptECB(unsigned char* c, long length, u1byte* m);
	void encryptCBC(unsigned char* c, long length, u1byte* m);
	void encryptCFB(unsigned char* c, long length, u1byte* m);
	void decryptECB(unsigned char* c, long length, u1byte* m);
	void decryptCBC(unsigned char* c, long length, u1byte* m);
	void decryptCFB(unsigned char* c, long length, u1byte* m);
};


