/*
 * @Author: Leon-Francis
 * @Contact: 15290552788@163.com
 * @Date: 2020-11-25 17:31:55
 * @LastEditTime: 2020-12-02 10:47:38
 * @LastEditors: Leon-Francis
 * @Description: 记录单词词法信息
 * @FilePath: /CompilerExperment/Tokenize.h
 * @(C)Copyright 2019-2020, Leon-Francis
 */
#include <vector>
#include <string>
#define KEYWORDNUM 32
#define OPERATORWORDNUM 36
#define DELIMETERNUM 12
#define KEYWORDMAXLEN 8
#define OPERATORWORDMAXLEN 3
#define DELIMETERMAXLEN 1
using namespace std;

typedef struct
{
    string name = "";
    int code = 0;
} Word;

typedef struct
{
    int label;    //单词序号
    string name = "";  //单词本身
    int code = 0;     //单词种别编码
    int addr = -1; //单词在符号表中的指针
    pair<int, int> pos; //单词在源文本中的位置
} WordToken;

typedef struct
{
    int number;      //序号
    string name = ""; //名字
    string type = "";     //类型
    //存储值
    string stringValue = "";
    int intValue = 0;
    double doubleValue = 0;

} WordSymble;

vector<WordToken> wordToken;
vector<WordSymble> wordSymble;

Word keyWord[KEYWORDNUM] = {{"auto", 1}, {"break", 2}, {"case", 3}, {"char", 4}, {"const", 5}, {"continue", 6}, {"default", 7}, {"do", 8}, {"double", 9}, {"else", 10}, {"enum", 11}, {"extend", 12}, {"float", 13}, {"for", 14}, {"goto", 15}, {"if", 16}, {"int", 17}, {"long", 18}, {"register", 19}, {"return", 20}, {"short", 21}, {"signed", 22}, {"sizeof", 23}, {"static", 24}, {"struct", 25}, {"switch", 26}, {"typedef", 27}, {"union", 28},{"unsigned", 29},{"void", 30}, {"volatile", 31}, {"while", 32}};
Word operatorWord[OPERATORWORDNUM] = {{"+", 33}, {"-", 34}, {"*", 35}, {"/", 36}, {"%", 37}, {"++", 38}, {"--", 39}, {"==", 40}, {"!=", 41}, {">", 42}, {"<", 43}, {">=", 44}, {"<=", 45}, {"&&", 46}, {"||", 47}, {"!", 48}, {"&", 49},{"|", 50}, {"^", 51}, {"~", 52}, {"<<", 53}, {">>", 54}, {"=", 55}, {"+=", 56}, {"-=", 57}, {"*=", 58}, {"/=", 59}, {"%=", 60}, {"<<=", 61}, {">>=", 62}, {"&=", 63}, {"^=", 64}, {"|=", 65}, {"&", 66}, {"*", 67}, {"?", 68}};
Word delimeter[DELIMETERNUM] = {{"{", 69}, {"}", 70}, {"(", 71}, {")", 72}, {"[", 73}, {"]", 74}, {":", 75}, {".", 76}, {";", 77}, {",", 78}, {"\'", 79}, {"\"", 80}};
