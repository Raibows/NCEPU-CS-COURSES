#include <cstdio>
#include <string.h>
class MD5
{
	typedef unsigned long int UINT4;

	typedef struct MD5_CTX
	{
		UINT4 state[4];         /* state (ABCD) */
		UINT4 count[2];        /* number of bits, modulo 2^64 (lsb first) */
		unsigned char buffer[64];       /* input buffer */
	} MD5_CTX;

	typedef unsigned char* POINTER;

	typedef unsigned short int UINT2;
public:
	void MD5Init(MD5_CTX*);
	void MD5Update(MD5_CTX*, unsigned char*, unsigned int);
	void MD5Final(unsigned char[16], MD5_CTX*);
	void MD5Transform(UINT4[4], unsigned char[64]);
	void Encode(unsigned char*, UINT4*, unsigned int);
	void Decode(UINT4*, unsigned char*, unsigned int);
	void MD5_memcpy(POINTER, POINTER, unsigned int);
	void MD5_memset(POINTER, int, unsigned int);
	void MD5_memchange(POINTER, UINT4*);
	int MD5File(unsigned char* filename1, unsigned char* output);
	void MD5String(unsigned char* inputData, unsigned char* hashstr);


};

