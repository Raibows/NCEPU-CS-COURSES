#include <cstdio>
#include <string.h>
class RC4
{
#define buf_size 8
#define swap_byte(x,y) t = *(x); *(x) = *(y); *(y) = t
	typedef struct rc4_key
	{
		unsigned char state[256];
		unsigned char x;
		unsigned char y;
	} rc4_key;
public:
	void prepare_key(unsigned char key_data_ptrp[256], int key_data_len, rc4_key* key);

	void rc4(unsigned char buffer_ptr[8], int buffer_len, rc4_key* key);

	int RC4File(char* filename1, char* filename2, char* session);

	void RC4String(char* keysession, unsigned char* inputdata, unsigned long inputlength, unsigned char* outputdata, unsigned long* outlength);

};

