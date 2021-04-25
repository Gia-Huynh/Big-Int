#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<stdint.h>
#include <bitset>
#include<string>

typedef unsigned char BYTE;
using namespace std;

typedef struct Bigint
{
    BYTE sign; // 1 is negative ,0 is positive
    int nbytes;
    BYTE* data;
} bigint;

void freedata(bigint x)
{
    delete[]x.data;
    x.data = NULL;
    x.nbytes = 0;
}

bool IsNonZero(string s)
{
    int n = s.length();
    for (int i = 0; i < n; i++)
    {
        if (s[i] != '0')
            return 1;
    }
    return 0;
}

int Getnumberofdigit(string s)
{
    return s.length();
}

int countbytes(string s)
{
    int carry = 0;
    string res = "";
    int a = 0;
    int cnt = 0;
    int n = Getnumberofdigit(s);
    while (IsNonZero(s))
    {
        for (int i = 0; i < n; i++)
        {
            a = carry * 10 + (s[i] - '0');
            res += (a / 256) + '0';
            carry = (a % 256);
        }
        cnt++;
        s = res;
        res = "";
        carry = 0;
    }
    return cnt;
}

void allocation(bigint& x, string s)
{
    x.nbytes = countbytes(s);
    x.data = new BYTE[x.nbytes];
}

void stringtobigint(bigint& x, string& s)
{
    int carry = 0;
    string res = "";
    int a = 0;
    int cnt = 0;
    int n = Getnumberofdigit(s);
    allocation(x, s);
    for (int i = 0; i < x.nbytes; i++)
    {
        for (int i = 0; i < n; i++)
        {
            a = carry * 10 + (s[i] - '0');
            res += (a / 256) + '0';
            carry = (a % 256);
        }
        x.data[i] = carry;
        s = res;
        res = "";
        carry = 0;
    }
}

string decimaltobinary(BYTE n)
{
    string str = "";
    while (n > 0)
    {
        str += (n % 2) + '0';
        n /= 2;
    }
    reverse(str.begin(), str.end());
    return str;
}

string BigintToBinary(bigint x)
{
    string str = "";
    for (int i = 0; i < x.nbytes; i++)
    {
        str += decimaltobinary(x.data[i]);
    }
    return str;
}

int Getdigit(string x, int pos)
{
    int n = x.length();
    if (pos < n)
        return x[pos] - '0';
    return 0;
}

string operator+(string x, string y)
{
    reverse(x.begin(), x.end());
    reverse(y.begin(), y.end());
    int nx = x.length();
    int ny = y.length();
    int n = (nx > ny) ? nx : ny;
    string str = "";
    int tmp;
    int mem = 0;
    for (int i = 0; i < n; i++)
    {
        int a = Getdigit(x, i);
        int b = Getdigit(y, i);
        tmp = a + b + mem;
        if (tmp >= 10)
        {
            tmp = tmp - 10;
            mem = 1;
        }
        else
        {
            mem = 0;
        }
        str += (tmp + '0');
    }
    if (mem)
    {
        str += "1";
    }
    reverse(str.begin(), str.end());
    return str;
}

string BigintToString(bigint x)
{
    string str = "";

    return str;
}

int main()
{
    string s = "256";
    string s1 = "0";
    bigint x;
    string t = s + s1;
    stringtobigint(x, t);
    cout << int(x.data[1]);
    freedata(x);
}