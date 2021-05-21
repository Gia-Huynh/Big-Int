#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<stdint.h>
#include <bitset>
#include<string>
#include<fstream>

typedef unsigned char BYTE;
using namespace std;

typedef struct Bigint
{
    BYTE sign = 0; // 1 is negative ,0 is positive
    int nbytes = 0;
    BYTE* data = NULL;
    void operator=(const Bigint& x)
    {
        if (nbytes && data != x.data)
        {
            delete[]data;
        }
        nbytes = x.nbytes;
        data = new BYTE[nbytes];
        for (int i = 0; i < nbytes; i++)
        {
            data[i] = x.data[i];
        }
        sign = x.sign;
    }
} bigint;

void freedata(bigint x);

bool StringNonZero(string s);

int Getnumberofdigit(string s);

int countbytes(string s);

void allocation(bigint& x, string s);

Bigint ShiftLeft(Bigint x);

bigint ShiftL(bigint x);

Bigint ShiftRight(Bigint x);

void copy(bigint& x, const bigint& y);

void DecimalToBigint(bigint& x, string s);

void Twocomplement(string& t);

string BinarySubstraction(string x, string y);

string BigintToNosignBinary(bigint x);

int CompareBinary(string x, string y);

string BigintToBinary(bigint x);

string AddBinary(string x, string y);

string BinarySubstraction(string x, string y);

string DecimalToBinary(BYTE n);

string BinaryMultiplication(string x, string y);

string BinaryDivision(string x, string y);

int BinaryToInt(string s);

void BinaryToBigint(bigint& x, string s);

int operator>(bigint x,bigint y);

bigint BigintAddition(bigint x, bigint y);

bigint BigintSubstraction(bigint x, bigint y);

bigint BigintMultiplication(bigint x, int num);

bigint BigintMod(const bigint& x, int num);

Bigint BigintModulo(const bigint& x, const bigint& y);

bigint operator+(bigint x, bigint y);

bigint operator-(bigint x,bigint y);

bigint operator*(bigint x, bigint y);

bigint operator/(const bigint& x, const bigint& y);

bigint operator%(const bigint &x,const bigint &y);

bigint power(const bigint& x, const bigint& y);

bigint operator~(const bigint& x);

bigint square(const bigint& x);

bool BigintIsNonZero(bigint x);

string BigintToDecimal(const bigint &x);

bigint BigintDivision(const bigint& x, int num);

int countspace(string t);
 
bigint Abs(const bigint &x);