#include<string>
using namespace std;
struct Word
{
	string name;
	int code;
};
struct Tokens
{
	int label;
	string name;
	int code;
	int addr = -1;
	string type;
	int linenum;
};
struct Symble
{
	int number;
	string type;
	string name;
};


struct WrongMessage {
	int number;
	int location;
	string name;
	string type;
};


WrongMessage wronginfo[100];
Tokens tokens[1000];
Symble symble[1000];
string alltext[100];

Word keyword[] = { { "and", 1 }, { "begin", 2 }, { "bool", 3 }, { "do", 4 },
{ "else", 5 }, { "end", 6 }, { "false", 7 }, { "if", 8 },
{ "integer", 9 }, { "not", 10 }, { "or", 11 }, { "program", 12 }, { "real", 13 }, { "then", 14 }, { "true", 15 }, { "var", 16 }, { "while", 17 } };
Word operatorword[] = { { "+", 23 }, { "-", 24 }, { "*", 25 }, { "/", 26 }, { ":=", 31 }, { "=", 32 }, { "<=", 33 }, { "<", 34 }, { "<>", 35 }, { ">", 36 }, { ">=", 37 } };
Word delimeter[] = { { "(", 21 }, { ")", 22 }, { ".", 27 }, { ",", 28 }, { ":", 29 }, { ";", 30 } };
