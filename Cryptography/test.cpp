#include "RC4.h"
#include "md5.h"
#include "AES.h"
#include <iostream>
#include<vector>
#include<string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
int main()
{
	const char HEX[16] = {
	'0', '1', '2', '3',
	'4', '5', '6', '7',
	'8', '9', 'a', 'b',
	'c', 'd', 'e', 'f'
	};
	int k;
	int y;
	cout << "         欢迎来到字符串/文件加密系统！         " << endl;
	cout << "***********************************************" << endl;
	do {
		cout << "选择方法:\n1.RC4  \n2.AES  \n3.MD5  " << endl;
		cout << "***********************************************" << endl;
		cin >> k;
		if (k == 1)//RC4
		{
			int l;
			cout << "请选择加/解密类型：1.字符串  2.文件 ，输入其他返回上一步" << endl;
			cin >> l;

			if (l == 1)
			{
				cout << "请输入密钥" << endl;
				unsigned char key[1000];
				cin >> key;
				RC4 rc4;
				unsigned char  revalue1[1000], revalue2[1000];
				unsigned char in[1000];
				cout << "请输入明/密文" << endl;
				cin >> in;
				unsigned long outlength;
				int i;
				for (i = 0; i < 1000; i++)
					revalue1[i] = 0;
				rc4.RC4String((char*)key, in, strlen((char*)in), revalue1, &outlength);
				printf("%s\n", revalue1);
			}
			else if (l == 2)
			{
				cout << "请输入密钥" << endl;
				unsigned char key[1000];
				cin >> key;
				RC4 rc4;
				int lxdyf;
				//char yflxd[20];
				char f1[200], f2[200];
				cout << "请输入加/解密文件路径" << endl;
				cin >> f1;
				cout << "请输入加/解密后，结果存放文件路径" << endl;
				cin >> f2;
				lxdyf = rc4.RC4File(f1, f2, (char*)key);
				if (lxdyf == 1)
					cout << "加/解密完成" << endl;
				/*else
				{
					cout << "加/解密失败" << endl;
					//_itoa_s(lxdyf, yflxd, 10);
					// MessageBox(NULL, yflxd, "Mistake",MB_OK|MB_ICONINFORMATION);
				}*/
			}
			else
			{
				l = 1;
			}
		}
		else if (k == 2)
		{
			cout << "请输入:\n1.选择加密" << endl;
			cout << "2.选择解密" << endl;
			cout << "***********************************************" << endl;
			cin >> y;
			if (y == 1)//AES加密
			{
				int x;
				cout << "请选择加密类型：\n1.字符串  \n2.文件" << endl;
				cout << "***********************************************" << endl;
				cin >> x;
				long lSize;
				unsigned char* c;
				AES aes;
				string str;
				if (x == 1) 
				{
					cout << "请输入明文：" << endl;
					cin >> str;
					c = (unsigned char*)(str.c_str());
					lSize = str.length();
				}
				else 
				{
					char f1[200];
					cout << "请输入需要加密的文件路径：" << endl;
					cin >> f1;
					FILE* fp1;
					errno_t err;
					err = fopen_s(&fp1, f1, "rb");
					if (err != 0)
					{
						cout << "打开源文件失败！" << endl;
						exit(1);
					}
					fseek(fp1, 0, SEEK_END);
					lSize = ftell(fp1);
					rewind(fp1);
					c = (unsigned char*)malloc(sizeof(char) * lSize);
					if (c == NULL)
					{
						cout << "分配内存失败！" << endl;
						exit(2);
					}
					size_t result = fread(c, 1, lSize, fp1);
					if (result != lSize)
					{
						fputs("读取失败！", stderr);
						exit(3);
					}
					fclose(fp1);
				}
				aes.tianchong(c, lSize);
				long a = lSize / 16 + 1;
				do {
					string key;
					cout << "请输入密钥(16字节)：" << endl;
					cin >> key;
					if (key.length() != 16)
						continue;
					else
					{
						u1byte* in_key = (unsigned char*)key.c_str();
						aes.set_key(in_key, 128);
						break;
					}
				} while (1);
				u1byte* m;
				int z;
				m = new u1byte[a * 16];

				cout << "请选择工作模式：[1]ECB  [2]CBC  [3]CFB" << endl;
				cin >> z;
				if (z == 1)
				{
					aes.encryptECB(c, a, m);

				}
				else if (z == 2)
				{
					aes.encryptCBC(c, a, m);
				}
				else
				{
					aes.encryptCFB(c, a, m);

				}
				if (x == 1)
				{
					cout << "密文为：";
					cout << m<<endl;
				
					/*cout << "***********************************************" << endl;
					cout << "选择方法:\n1.RC4  \n2.AES  \n3.MD5  \n4.DES" << endl;
					cout << "***********************************************" << endl;
					cin >> k;*/
				}
				else
				{
					char f2[200];
					cout << "请输入加密后，结果存放密文的文件路径：" << endl;
					cin >> f2;
					FILE* fp1;
					errno_t err;
					err = fopen_s(&fp1, f2, "wb");
					if (err != 0)
					{
						cout << "打开目标文件失败！" << endl;
						exit(1);
					}
					size_t result = fwrite(m, 1, a * 16, fp1);
					if (result != a * 16)
					{
						fputs("存储失败！", stderr);
						exit(3);
					}
					fclose(fp1);
					cout << "存放成功！\n";
					cout << "***********************************************" << endl;
				}
				
			}
			else if (y == 2)//AES解密
			{
				int x;
				cout << "请选择解密类型：\n1.字符串  \n2.文件" << endl;
				cout << "***********************************************" << endl;
				cin >> x;
				long lSize;
				unsigned char* c;
				AES aes;
				string str;
				if (x == 1) {//AES解密字符串
					cout << "请输入需要解密的密文：" << endl;
					cin >> str;
					c = (unsigned char*)(str.c_str());
					lSize = str.length();
				}
				else {//AES解密文件
					char f1[200];
					cout << "请输入需要解密的文件路径：" << endl;
					cin >> f1;
					FILE* fp1;
					errno_t err;
					err = fopen_s(&fp1, f1, "rb");
					if (err != 0)
					{
						cout << "打开原文件失败！" << endl;
						exit(1);
					}
					fseek(fp1, 0, SEEK_END);
					lSize = ftell(fp1);
					rewind(fp1);
					c = (unsigned char*)malloc(sizeof(char) * lSize);
					if (c == NULL)
					{
						cout << "分配内存失败！" << endl;
						exit(2);
					}
					size_t result = fread(c, 1, lSize, fp1);
					if (result != lSize)
					{
						fputs("读取失败！", stderr);
						exit(3);
					}
					fclose(fp1);
				}
				long a = lSize / 16;
				do {
					string key;
					cout << "请输入密钥(16字节)：" << endl;
					cin >> key;
					if (key.length() != 16)
						continue;
					else
					{
						u1byte* in_key = (unsigned char*)key.c_str();
						aes.set_key(in_key, 128);
						break;
					}
				} while (1);
				u1byte* m;
				int z;
				m = new u1byte[a * 16];
				cout << "***********************************************" << endl;
				cout << "请选择工作模式：[1]ECB  [2]CBC  [3]CFB" << endl;
				cout << "***********************************************" << endl;
				cin >> z;
				if (z == 1)
				{
					aes.decryptECB(c, a, m);
					
				}
				else if (z == 2)
				{
					aes.decryptCBC(c, a, m);
					
				}
				else if(z==3)
				{
					aes.decryptCFB(c, a, m);
				}
				a = aes.untianchong(m, a * 16);
				
				if (x == 1)
				{
					cout << "密文为：";
					
					cout << m<<endl;
				
					/*cout << "***********************************************" << endl;
					cout << "选择方法:\n1.RC4  \n2.AES  \n3.MD5  \n4.DES" << endl;
					cout << "***********************************************" << endl;

					cin >> k;*/
				}
				else
				{
					char f2[200];
					cout << "请输入解密后，结果存放明文的文件路径：" << endl;
					cin >> f2;
					FILE* fp1;
					errno_t err;
					err = fopen_s(&fp1, f2, "wb");
					if (err != 0)
					{
						cout << "打开目标文件失败！" << endl;
						exit(1);
					}
					size_t result = fwrite(m, 1, a, fp1);
					if (result != a)
					{
						size_t result = fwrite(m, 1, strlen((char*)m), fp1);
						/*fputs("存储失败！", stderr);
						exit(3);*/
					}
					fclose(fp1);
					cout << "存放成功！\n";
					cout << "***********************************************" << endl;
					
				}
				
			}
			else
			{
				y = 1;
			}
		}
		else if (k == 3)//md5
		{
			int x;
			cout << "请选择加密类型：\n1.字符串  \n2.文件" << endl;
			cin >> x;
			RC4 rc4;
			if (x == 1)//md5加密字符串
			{
				unsigned char* inputData;
				char* inp = (char*)malloc(sizeof(char) * 1024);
				inputData = (unsigned char*)inp;
				unsigned char* hashstr;
				//int i,x;
				//int len;
				MD5 md5;

				cout << "请输入要加密的字符串：\n";
				cin>>inputData;
				if ((hashstr = (unsigned char*)malloc(17)) == NULL)
				{
					cout << "没有足够的内存！";
					exit(1);
				}


				md5.MD5String(inputData, hashstr);

				int len = strlen((char*)hashstr);

				string str;
				str.reserve(len << 1);

				for (int i = 0; i < len; i++) {
					int t = hashstr[i];
					int a = t / 16;
					int b = t % 16;
					str.append(1, HEX[a]);
					str.append(1, HEX[b]);

				}

				cout << "哈希值为：";
				cout << str;
				cout << endl;
				free(hashstr);
				cout << "***********************************************" << endl;
			}
			else if (x == 2)////md5加密文件
			{
				int lxdyf;

				unsigned char f1[200];
				unsigned char* output;
				MD5 md5;
				cout << "请输入需要加密的文件路径：" << endl;
				cin >> f1;
				if ((output = (unsigned char*)malloc(17)) == NULL)
				{
					cout << "没有足够的内存！";
					exit(1);
				}
				lxdyf = md5.MD5File(f1, output);

				int len = strlen((char*)output);
				string str;
				str.reserve(16 << 1);
				for (int i = 0; i < 16; i++) {
					int t = output[i];
					int a = t / 16;
					int b = t % 16;
					str.append(1, HEX[a]);
					str.append(1, HEX[b]);
				}

				if (lxdyf == 1)
				{
					cout << "加密完成！" << endl;
					cout << "哈希值为：";
					cout << str << endl;
					cout << "***********************************************" << endl;
					char f2[200];
					char p[128];
					int i;
					for (i = 0;i < str.length();i++)
						p[i] = str[i];
					p[i] = '\0';
					cout << "请输入加密结果存放路径" << endl;
					cin >> f2;
					FILE* fp1;
					errno_t err;
					err = fopen_s(&fp1, f2, "wb");
					if (err != 0)
					{
						cout << "打开目标文件失败" << endl;
						exit(1);
					}
					size_t result = fwrite(p, 1, 32, fp1);
					if (result != 32)
					{
						fputs("存储失败！", stderr);
						exit(3);
					}
					fclose(fp1);
					cout << "存放成功！" << endl;
					cout << "***********************************************" << endl;
				}

				else
				{
					cout << "加/解密失败！" << endl;
				}
				free(output);
			}
		}
	} while (k != 5);
	return 0;
}


