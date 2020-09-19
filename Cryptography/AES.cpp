#include "AES.h"
#include<string>
#include <iostream>
using namespace std;

#define LARGE_TABLES


u1byte  pow_tab[256];
u1byte  log_tab[256];
u1byte  sbx_tab[256];
u1byte  isb_tab[256];
u4byte  rco_tab[10];
u4byte  ft_tab[4][256];
u4byte  it_tab[4][256];

#ifdef  LARGE_TABLES
u4byte  fl_tab[4][256];
u4byte  il_tab[4][256];
#endif

u4byte  tab_gen = 0;

#define ff_mult(a,b)    (a && b ? pow_tab[(log_tab[a] + log_tab[b]) % 255] : 0)

#define f_rn(bo, bi, n, k)                          \
    bo[n] =  ft_tab[0][byte(bi[n],0)] ^             \
             ft_tab[1][byte(bi[(n + 1) & 3],1)] ^   \
             ft_tab[2][byte(bi[(n + 2) & 3],2)] ^   \
             ft_tab[3][byte(bi[(n + 3) & 3],3)] ^ *(k + n)

#define i_rn(bo, bi, n, k)                          \
    bo[n] =  it_tab[0][byte(bi[n],0)] ^             \
             it_tab[1][byte(bi[(n + 3) & 3],1)] ^   \
             it_tab[2][byte(bi[(n + 2) & 3],2)] ^   \
             it_tab[3][byte(bi[(n + 1) & 3],3)] ^ *(k + n)

#ifdef LARGE_TABLES

#define ls_box(x)                \
    ( fl_tab[0][byte(x, 0)] ^    \
      fl_tab[1][byte(x, 1)] ^    \
      fl_tab[2][byte(x, 2)] ^    \
      fl_tab[3][byte(x, 3)] )

#define f_rl(bo, bi, n, k)                          \
    bo[n] =  fl_tab[0][byte(bi[n],0)] ^             \
             fl_tab[1][byte(bi[(n + 1) & 3],1)] ^   \
             fl_tab[2][byte(bi[(n + 2) & 3],2)] ^   \
             fl_tab[3][byte(bi[(n + 3) & 3],3)] ^ *(k + n)

#define i_rl(bo, bi, n, k)                          \
    bo[n] =  il_tab[0][byte(bi[n],0)] ^             \
             il_tab[1][byte(bi[(n + 3) & 3],1)] ^   \
             il_tab[2][byte(bi[(n + 2) & 3],2)] ^   \
             il_tab[3][byte(bi[(n + 1) & 3],3)] ^ *(k + n)

#else

#define ls_box(x)                            \
    ((u4byte)sbx_tab[byte(x, 0)] <<  0) ^    \
    ((u4byte)sbx_tab[byte(x, 1)] <<  8) ^    \
    ((u4byte)sbx_tab[byte(x, 2)] << 16) ^    \
    ((u4byte)sbx_tab[byte(x, 3)] << 24)

#define f_rl(bo, bi, n, k)                                      \
    bo[n] = (u4byte)sbx_tab[byte(bi[n],0)] ^                    \
        rotl(((u4byte)sbx_tab[byte(bi[(n + 1) & 3],1)]),  8) ^  \
        rotl(((u4byte)sbx_tab[byte(bi[(n + 2) & 3],2)]), 16) ^  \
        rotl(((u4byte)sbx_tab[byte(bi[(n + 3) & 3],3)]), 24) ^ *(k + n)

#define i_rl(bo, bi, n, k)                                      \
    bo[n] = (u4byte)isb_tab[byte(bi[n],0)] ^                    \
        rotl(((u4byte)isb_tab[byte(bi[(n + 3) & 3],1)]),  8) ^  \
        rotl(((u4byte)isb_tab[byte(bi[(n + 2) & 3],2)]), 16) ^  \
        rotl(((u4byte)isb_tab[byte(bi[(n + 1) & 3],3)]), 24) ^ *(k + n)

#endif
void AES::tianchong(unsigned char* c, long length)
{
	int yu = length % 16;
	c[length] = 0x80;
	if (yu == 0)
	{
		for (int i = 1;i < 16;i++)
			c[length + i] = 0x00;
	}
	else {
		for (int i = 1;i < 16-yu;i++)
			c[length + i] = 0x00;
	}
	/*c[length++] = 0x80;
	for (; length % 16 != 0; length++)
	{
		c[length] = 0x00;
	}*/
}

long AES::untianchong(unsigned char* c, long length)
{
	while (c[length - 1] != 0x80)
		length--;
	return --length;
	

}

void gen_tabs(void)//计算轮常数
{
	u4byte  i, t;
	u1byte  p, q;  

	for (i = 0, p = 1; i < 256; ++i)
	{
		pow_tab[i] = (u1byte)p; 
		log_tab[p] = (u1byte)i;

		p = p ^ (p << 1) ^ (p & 0x80 ? 0x01b : 0);
	}

	log_tab[1] = 0; p = 1;

	for (i = 0; i < 10; ++i)
	{
		rco_tab[i] = p;

		p = (p << 1) ^ (p & 0x80 ? 0x1b : 0);
	}

	for (i = 0; i < 256; ++i)
	{
		p = (i ? pow_tab[255 - log_tab[i]] : 0); q = p;
		q = (q >> 7) | (q << 1); p ^= q;
		q = (q >> 7) | (q << 1); p ^= q;
		q = (q >> 7) | (q << 1); p ^= q;
		q = (q >> 7) | (q << 1); p ^= q ^ 0x63;
		sbx_tab[i] = p; isb_tab[p] = (u1byte)i;
	}

	for (i = 0; i < 256; ++i)
	{
		p = sbx_tab[i];

#ifdef  LARGE_TABLES        

		t = p; fl_tab[0][i] = t;
		fl_tab[1][i] = rotl(t, 8);
		fl_tab[2][i] = rotl(t, 16);
		fl_tab[3][i] = rotl(t, 24);
#endif
		t = ((u4byte)ff_mult(2, p)) |
			((u4byte)p << 8) |
			((u4byte)p << 16) |
			((u4byte)ff_mult(3, p) << 24);

		ft_tab[0][i] = t;
		ft_tab[1][i] = rotl(t, 8);
		ft_tab[2][i] = rotl(t, 16);
		ft_tab[3][i] = rotl(t, 24);

		p = isb_tab[i];

#ifdef  LARGE_TABLES        

		t = p; il_tab[0][i] = t;
		il_tab[1][i] = rotl(t, 8);
		il_tab[2][i] = rotl(t, 16);
		il_tab[3][i] = rotl(t, 24);
#endif 
		t = ((u4byte)ff_mult(14, p)) |
			((u4byte)ff_mult(9, p) << 8) |
			((u4byte)ff_mult(13, p) << 16) |
			((u4byte)ff_mult(11, p) << 24);

		it_tab[0][i] = t;
		it_tab[1][i] = rotl(t, 8);
		it_tab[2][i] = rotl(t, 16);
		it_tab[3][i] = rotl(t, 24);
	}

	tab_gen = 1;
}

#define star_x(x) (((x) & 0x7f7f7f7f) << 1) ^ ((((x) & 0x80808080) >> 7) * 0x1b)

#define imix_col(y,x)       \
    u   = star_x(x);        \
    v   = star_x(u);        \
    w   = star_x(v);        \
    t   = w ^ (x);          \
   (y)  = u ^ v ^ w;        \
   (y) ^= rotr(u ^ t,  8) ^ \
          rotr(v ^ t, 16) ^ \
          rotr(t,24)
 

#define loop4(i)                                    \
{   t = ls_box(rotr(t,  8)) ^ rco_tab[i];           \
    t ^= e_key[4 * i];     e_key[4 * i + 4] = t;    \
    t ^= e_key[4 * i + 1]; e_key[4 * i + 5] = t;    \
    t ^= e_key[4 * i + 2]; e_key[4 * i + 6] = t;    \
    t ^= e_key[4 * i + 3]; e_key[4 * i + 7] = t;    \
}

#define loop6(i)                                    \
{   t = ls_box(rotr(t,  8)) ^ rco_tab[i];           \
    t ^= e_key[6 * i];     e_key[6 * i + 6] = t;    \
    t ^= e_key[6 * i + 1]; e_key[6 * i + 7] = t;    \
    t ^= e_key[6 * i + 2]; e_key[6 * i + 8] = t;    \
    t ^= e_key[6 * i + 3]; e_key[6 * i + 9] = t;    \
    t ^= e_key[6 * i + 4]; e_key[6 * i + 10] = t;   \
    t ^= e_key[6 * i + 5]; e_key[6 * i + 11] = t;   \
}

#define loop8(i)                                    \
{   t = ls_box(rotr(t,  8)) ^ rco_tab[i];           \
    t ^= e_key[8 * i];     e_key[8 * i + 8] = t;    \
    t ^= e_key[8 * i + 1]; e_key[8 * i + 9] = t;    \
    t ^= e_key[8 * i + 2]; e_key[8 * i + 10] = t;   \
    t ^= e_key[8 * i + 3]; e_key[8 * i + 11] = t;   \
    t  = e_key[8 * i + 4] ^ ls_box(t);              \
    e_key[8 * i + 12] = t;                          \
    t ^= e_key[8 * i + 5]; e_key[8 * i + 13] = t;   \
    t ^= e_key[8 * i + 6]; e_key[8 * i + 14] = t;   \
    t ^= e_key[8 * i + 7]; e_key[8 * i + 15] = t;   \
}

void AES::set_key(const u1byte in_key[], const u4byte key_len)//扩展密钥
{
	u4byte  i, t, u, v, w;

	if (!tab_gen)

		gen_tabs();

	k_len = (key_len + 31) / 32;

	e_key[0] = u4byte_in(in_key);
	e_key[1] = u4byte_in(in_key + 4);
	e_key[2] = u4byte_in(in_key + 8);
	e_key[3] = u4byte_in(in_key + 12);

	switch (k_len)
	{
	case 4: t = e_key[3];
		for (i = 0; i < 10; ++i)
			loop4(i);
		break;

	case 6: e_key[4] = u4byte_in(in_key + 16); t = e_key[5] = u4byte_in(in_key + 20);
		for (i = 0; i < 8; ++i)
			loop6(i);
		break;

	case 8: e_key[4] = u4byte_in(in_key + 16); e_key[5] = u4byte_in(in_key + 20);
		e_key[6] = u4byte_in(in_key + 24); t = e_key[7] = u4byte_in(in_key + 28);
		for (i = 0; i < 7; ++i)
			loop8(i);
		break;
	}

	d_key[0] = e_key[0]; d_key[1] = e_key[1];
	d_key[2] = e_key[2]; d_key[3] = e_key[3];

	for (i = 4; i < 4 * k_len + 24; ++i)
	{
		imix_col(d_key[i], e_key[i]);
	}

	return;
}



#define f_nround(bo, bi, k) \
    f_rn(bo, bi, 0, k);     \
    f_rn(bo, bi, 1, k);     \
    f_rn(bo, bi, 2, k);     \
    f_rn(bo, bi, 3, k);     \
    k += 4

#define f_lround(bo, bi, k) \
    f_rl(bo, bi, 0, k);     \
    f_rl(bo, bi, 1, k);     \
    f_rl(bo, bi, 2, k);     \
    f_rl(bo, bi, 3, k)

//void rijndael::encrypt(const u1byte in_blk[16], u1byte out_blk[16])
void AES::encrypt(const u1byte in_blk[16], u1byte out_blk[16])//加密
{
	u4byte  b0[4], b1[4], * kp;

	b0[0] = u4byte_in(in_blk) ^ e_key[0]; b0[1] = u4byte_in(in_blk + 4) ^ e_key[1];
	b0[2] = u4byte_in(in_blk + 8) ^ e_key[2]; b0[3] = u4byte_in(in_blk + 12) ^ e_key[3];

	kp = e_key + 4;

	if (k_len > 6)
	{
		f_nround(b1, b0, kp); f_nround(b0, b1, kp);
	}

	if (k_len > 4)
	{
		f_nround(b1, b0, kp); f_nround(b0, b1, kp);
	}

	f_nround(b1, b0, kp); f_nround(b0, b1, kp);
	f_nround(b1, b0, kp); f_nround(b0, b1, kp);
	f_nround(b1, b0, kp); f_nround(b0, b1, kp);
	f_nround(b1, b0, kp); f_nround(b0, b1, kp);
	f_nround(b1, b0, kp); f_lround(b0, b1, kp);//10轮

	u4byte_out(out_blk, b0[0]); u4byte_out(out_blk + 4, b0[1]);
	u4byte_out(out_blk + 8, b0[2]); u4byte_out(out_blk + 12, b0[3]);//密文
}

// decrypt a block of text  

#define i_nround(bo, bi, k) \
    i_rn(bo, bi, 0, k);     \
    i_rn(bo, bi, 1, k);     \
    i_rn(bo, bi, 2, k);     \
    i_rn(bo, bi, 3, k);     \
    k -= 4

#define i_lround(bo, bi, k) \
    i_rl(bo, bi, 0, k);     \
    i_rl(bo, bi, 1, k);     \
    i_rl(bo, bi, 2, k);     \
    i_rl(bo, bi, 3, k)

//void rijndael::decrypt(const u1byte in_blk[16], u1byte out_blk[16])
void AES::decrypt(const u1byte in_blk[16], u1byte out_blk[16])//解密
{
	u4byte  b0[4], b1[4], * kp;

	b0[0] = u4byte_in(in_blk) ^ e_key[4 * k_len + 24];
	b0[1] = u4byte_in(in_blk + 4) ^ e_key[4 * k_len + 25];
	b0[2] = u4byte_in(in_blk + 8) ^ e_key[4 * k_len + 26];
	b0[3] = u4byte_in(in_blk + 12) ^ e_key[4 * k_len + 27];

	kp = d_key + 4 * (k_len + 5);

	if (k_len > 6)
	{
		i_nround(b1, b0, kp); i_nround(b0, b1, kp);
	}

	if (k_len > 4)
	{
		i_nround(b1, b0, kp); i_nround(b0, b1, kp);
	}

	i_nround(b1, b0, kp); i_nround(b0, b1, kp);
	i_nround(b1, b0, kp); i_nround(b0, b1, kp);
	i_nround(b1, b0, kp); i_nround(b0, b1, kp);
	i_nround(b1, b0, kp); i_nround(b0, b1, kp);
	i_nround(b1, b0, kp); i_lround(b0, b1, kp);

	u4byte_out(out_blk, b0[0]); u4byte_out(out_blk + 4, b0[1]);
	u4byte_out(out_blk + 8, b0[2]); u4byte_out(out_blk + 12, b0[3]);//明文
}


void AES::encryptECB(unsigned char* c, long length, u1byte* m)//ecb模式加密，m为密文
{
	u1byte c_block[16], out_block[16];//明密文矩阵
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			c_block[j] = c[i * 16 + j];//初始化明文矩阵
		}
		encrypt(c_block, out_block);//加密
		for (int w = 0; w < 16; w++)
		{
			m[i * 16 + w] = out_block[w];//密文
		}
	}
}

void AES::encryptCBC(unsigned char* c, long length, u1byte* m)//cbc模式加密
{
	char ci[16];
	for (int i = 0; i < 16; i++)
		ci[i] = 0;//初始向量全零
	u1byte temp[16], out_block[16];
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			temp[j] = c[i * 16 + j] ^ ci[j];//明文与初始向量异或后进行加密
		}
		encrypt(temp, out_block);//加密

		for (int w = 0; w < 16; w++)
		{
			ci[w] = out_block[w];//更新初始向量
			m[i * 16 + w] = out_block[w];//密文
		}
	}

}
void AES::encryptCFB(unsigned char* c, long length, u1byte* m)
{
	u1byte R[16];
	for (int i = 0; i < 16; i++)
		R[i] = 0;//移位寄存器初始化，全零
	u1byte c_block[16], out_block[16];
	for (int i = 0; i < length * 16; i++)
	{
		encrypt(R, out_block);//对移位寄存器内容加密
		m[i] = out_block[0] ^ c[i];//加密后内容与明文异或生成密文
		for (int w = 0; w < 15; w++)
		{
			R[w] = R[w + 1];
		}
		R[15] = m[i];//移位，并将密文放在最后面
	}
}
void AES::decryptECB(unsigned char* c, long length, u1byte* m)
{
	u1byte c_block[16], out_block[16];
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			c_block[j] = c[i * 16 + j];
		}
		decrypt(c_block, out_block);
		for (int w = 0; w < 16; w++)
		{
			m[i * 16 + w] = out_block[w];
		}
	}
}
void AES::decryptCBC(unsigned char* c, long length, u1byte* m)
{
	char ci[16];
	for (int i = 0; i < 16; i++)
		ci[i] = 0;
	u1byte temp[16], c_block[16], out_block[16];
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			c_block[j] = c[i * 16 + j];
		}
		decrypt(c_block, out_block);
		for (int w = 0; w < 16; w++)
		{
			temp[w] = out_block[w] ^ ci[w];
			m[i * 16 + w] = temp[w];
			ci[w] = c_block[w];
		}
	}

}
void AES::decryptCFB(unsigned char* c, long length, u1byte* m)
{
	u1byte R[16];
	for (int i = 0; i < 16; i++)
		R[i] = 0;
	u1byte c_block[16], out_block[16];
	for (int i = 0; i < length * 16; i++)
	{
		encrypt(R, out_block);
		m[i] = out_block[0] ^ c[i];
		for (int w = 0; w < 15; w++)
		{
			R[w] = R[w + 1];
		}
		R[15] = c[i];
	}
}