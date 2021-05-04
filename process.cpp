#include"process.h"

void freedata(bigint x)
{
    if(x.data!=NULL)
        delete[]x.data;
    x.data = NULL;
    x.nbytes = 0;
}

bool StringNonZero(string s)
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
    while (StringNonZero(s))
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

Bigint ShiftLeft(Bigint x) {
    bigint res;
    res.sign = x.sign;
    res.nbytes = x.nbytes - 1;
    res.data = new BYTE[res.nbytes];
    for (int i = 0; i < x.nbytes - 1; i++)
        res.data[i] = x.data[i];
    return res;
}

bigint ShiftL(bigint x)
{
    bigint res;
    res.sign = x.sign;
    res.nbytes = x.nbytes + 1;
    res.data = new BYTE[res.nbytes];
    for (int i = 0; i < x.nbytes; i++)
        res.data[i+1] = x.data[i];
    res.data[0] = 0;
    return res;
}

Bigint ShiftRight(Bigint x) {
    bigint res;
    res.sign = x.sign;
    res.nbytes = x.nbytes + 1;
    res.data = new BYTE[res.nbytes];
    for (int i = 0; i < x.nbytes; i++)
        res.data[i] = x.data[i];
    res.data[x.nbytes] = 0;
    return res;
}

void copy(bigint& x, const bigint& y)
{
    if (x.data != NULL)
       delete[]x.data;
    x.nbytes = y.nbytes;
    x.data = y.data;
    x.sign = y.sign;
}

bigint ReverseBigint(bigint x)
{
    bigint res;
    int n = x.nbytes;
    res.nbytes = x.nbytes;
    res.data = new BYTE[res.nbytes];
    res.sign = x.sign;
    for (int i = 0; i < n; i++)
    {
        res.data[i] = x.data[n - 1 - i];
    }
    return res;
}

void DecimalToBigint(bigint& x, string s)
{
    if (s == "0")
    {
        x.data = new BYTE[1];
        x.data[0] = 0;
        x.sign = 0;
        x.nbytes = 1;
    }
    else
    {
        if (s[0] == '-')
        {
            x.sign = 1;
            s.erase(s.begin());
        }
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
}

string DecimalToBinary(BYTE n)
{
    string str = "";
    int cnt = 0;
    while (n > 0)
    {
        str += (n % 2) + '0';
        n /= 2;
        cnt++;
    }
    while (cnt < 8)
    {
        str += "0";
        cnt++;
    }
    reverse(str.begin(), str.end());
    return str;
}

void Twocomplement(string& t)
{
    int tmp = 0;
    int n = t.length();
    for (int i = 0; i < n; i++)
    {
        tmp = t[i] - '0';
        t[i] = (1 - tmp) + '0';
    }
    t = AddBinary(t, "1");
}

string BigintToNosignBinary(bigint x)
{
    string str = "";
    for (int i = x.nbytes - 1; i >= 0; i--)
    {
        str += DecimalToBinary(x.data[i]);
    }
    int i = 0;
    while (str[i] == '0')
    {
        str.erase(str.begin());
    }
    return str;
}

int CompareBinary(string x, string y)
{
    while (x[0] == '0')
        x.erase(x.begin());
    while (y[0] == '0')
        y.erase(y.begin());
    int nx = x.length();
    int ny = y.length();
    if (ny > nx)
        return -1;
    if (x == y)
        return 0;
    if (nx == ny)
    {
        for (int i = 0; i < nx; i++)
        {
            if (x[i] > y[i])
                return 1;
            if (y[i] > x[i])
                return -1;
        }
    }
    return 1;
}


string BigintToBinary(bigint x)
{

    string str = "0";
    str += BigintToNosignBinary(x);
    if (x.sign == 1)
        Twocomplement(str);
    return str;
}

string AddBinary(string x, string y)
{
    reverse(x.begin(), x.end());
    reverse(y.begin(), y.end());
    int nx = x.length();
    int ny = y.length();
    int n = (nx > ny) ? nx : ny;
    int carry = 0;
    int a = 0;
    string str = "";
    if (n - nx > 0)
        for (int i = nx; i < n; i++)
        {
            x += "0";
        }
    else
        for (int i = ny; i < n; i++)
            y += "0";
    for (int i = 0; i < n; i++)
    {
        a = (x[i] - '0') + (y[i] - '0') + carry;
        if (a > 1)
        {
            a = a - 2;
            carry = 1;
        }
        else
            carry = 0;
        str += a + '0';
    }
    if (carry > 0)
        str += "1";
    reverse(str.begin(), str.end());
    while (str[0] == '0')
        str.erase(str.begin());
    return str;
}

string BinarySubstraction(string x, string y)
{
    string res = "";
    int nx = x.length();
    int ny = y.length();
    int tmp = 0;
    int mem = 0;
    reverse(x.begin(), x.end());
    reverse(y.begin(), y.end());
    for (int i = 0; i < ny; i++)
    {
        tmp = (x[i] - '0') - (y[i] - '0') - mem;
        if (tmp < 0)
        {
            tmp = (x[i] - '0') + 2 - (y[i] - '0') - mem;
            mem = 1;
        }
        else
            mem = 0;
        res += tmp + '0';
    }
    for (int i = ny; i < nx; i++)
    {
        if (mem > 0)
        {
            tmp = (x[i] - '0') - mem;
            mem = 0;
            res += tmp + '0';
        }
        else
            res += x[i];
    }
    reverse(res.begin(), res.end());
    return res;
}

string BinaryMultiplication(string x, string y)
{
    int nx = x.length();
    int ny = y.length();
    string res = "";
    string tmp = "";
    string mem = "";
    if (y == "0")
    {
        return "0";
    }
    if (y == "1")
        return x;
    reverse(x.begin(), x.end());
    reverse(y.begin(), y.end());
    for (int i = 0; i < ny; i++)
    {
        if (i >= 1)
            mem += "0";
        tmp += mem;
        for (int j = 0; j < nx; j++)
        {
            if (x[j] == '1' && y[i] == '1')
            {
                tmp += "1";
            }
            else
                tmp += "0";
        }
        reverse(tmp.begin(), tmp.end());
        res = AddBinary(res, tmp);
        tmp = "";
    }
    return res;
}

string BinaryDivision(string x, string y)
{
    string res;
    string tmp = "";
    int nx = x.length();
    int ny = y.length();
    for (int i = 0; i < nx; i++)
    {
        tmp += x[i];
        if (CompareBinary(tmp, y) != -1)
        {
            tmp = BinarySubstraction(tmp, y);
            res += "1";
        }
        else
            res += "0";
    }
    int n = res.length();
    while (res[0] == '0' && n > 0)
    {
        res.erase(res.begin());
        n--;
    }
    return res;
}

int BinaryToInt(string s)
{
    int res = 0;
    int n = s.length();
    int carry = 1;
    for (int i = n - 1; i >= 0; i--)
    {
        res = res + (s[i] - '0') * carry;
        carry = carry * 2;
    }
    return res;
}

void BinaryToBigint(bigint& x, string s)
{
    if (s[0] == '1')
    {
        int k = s.length();
        x.sign = 1;
        s = BinarySubstraction(s, "1");
        for (int i = 0; i < k; i++)
        {
            int tmp = 1 - (s[i] - '0');
            s[i] = tmp + '0';
        }
    }
    s.erase(s.begin());
    int n = s.length();
    int k = (8 - n % 8) % 8;
    reverse(s.begin(), s.end());
    for (int i = 0; i < k; i++)
    {
        s += "0";
    }
    reverse(s.begin(), s.end());
    int cnt = (n + k) / 8;
    x.nbytes = cnt;
    x.data = new BYTE[x.nbytes];
    for (int j = 0; j < cnt; j++)
    {
        string str = "";
        for (int i = 8 * j; i < 8 * (j + 1); i++)
        {
            str += s[i];
        }
        x.data[cnt - 1 - j] = BinaryToInt(str);
    }
}


int operator>(bigint x,bigint y)
{
     bigint tmp_x;
    bigint tmp_y;
    tmp_x = x;
    tmp_y = y;
    int nx = x.nbytes;
    int ny = y.nbytes;
    int n = (nx > ny) ? nx : ny;
    while (n > nx)
    {
        copy(tmp_x, ShiftRight(tmp_x));
        nx++;
    }
    while (n > ny)
    {
        copy(tmp_y, ShiftRight(tmp_y));
        ny++;
    }
    
    for (int i = n-1; i >=0; i--)
    {
        if (tmp_x.data[i] > tmp_y.data[i])
        {
            freedata(tmp_x);
            freedata(tmp_y);
            return 1;
        }
        if (tmp_x.data[i] < tmp_y.data[i])
        {
            freedata(tmp_x);
            freedata(tmp_y);
            return -1;
        }
    }
    freedata(tmp_x);
    freedata(tmp_y);
    return 0;
}

bigint BigintAddition(bigint x,bigint y)
{
    bigint res;
    int nx = x.nbytes;
    int ny = y.nbytes;
    int n = (nx > ny) ? nx : ny;
    int mem = 0;
    res.data = new BYTE[n + 1];
    if (n - ny > 0)
    {
        for (int i = 0; i < n; i++)
        {
            if (i < ny)
            {
                res.data[i] = x.data[i] + y.data[i] + mem;
                if (int(x.data[i] + y.data[i]) > 255)
                    mem = 1;
                else
                    mem = 0;
            }
            else
            {
                res.data[i] = x.data[i] + mem;
                if (int(x.data[i]) + mem > 255)
                    mem = 1;
                else
                    mem = 0;
            }
        }
    }
    else
        if (n - nx > 0)
        {
            for (int i = 0; i < n; i++)
            {
                if (i < nx)
                {
                    res.data[i] = x.data[i] + y.data[i] + mem;
                    if (int(x.data[i] + y.data[i] + mem) > 255)
                        mem = 1;
                    else
                        mem = 0;
                }
                else
                {
                    res.data[i] = y.data[i] + mem;
                    if (int(y.data[i] + mem) + mem > 255)
                        mem = 1;
                    else
                        mem = 0;
                }
            }
        }
        else
        {
            for (int i = 0; i < n; i++)
            {
                res.data[i] = x.data[i] + y.data[i] + mem;
                if (x.data[i] + y.data[i] + mem > 255)
                    mem = 1;
                else
                    mem = 0;
            }
            if (mem)
            {
                res.data[n] = mem;
                n++;
            }
        }
    res.nbytes = n;
    return res;
}

bigint BigintSubstraction(bigint x,bigint y)
{
    bigint res;
    int nx = x.nbytes;
    int ny = y.nbytes;
    bigint tmp_x;
    tmp_x = x;
    bigint tmp_y;
    tmp_y = y;
    int n = (nx > ny) ? nx : ny;
    while (n > nx)
    {
        copy(tmp_x, ShiftRight(tmp_x));
        nx++;
    }
    while (n > ny)
    {
        copy(tmp_y, ShiftRight(tmp_y));
        ny++;
    }
    int tmp = 0;
    int mem = 0;
    res.data = new BYTE[n];
    for (int i = 0; i < n; i++)
    {
        tmp = tmp_x.data[i] - tmp_y.data[i] - mem;
        if (tmp < 0)
        {
            tmp = tmp + 256;
            mem = 1;
        }
        else
            mem = 0;
        res.data[i] = tmp;
    }
    while (res.data[res.nbytes - 1] == 0)
    {
        copy(res, ShiftLeft(res));
        n--;
    }
    res.nbytes = n;
    freedata(tmp_x);
    freedata(tmp_y);
    return res;
}
bigint BigintMultiplication( bigint x, int num)
{
    bigint res;
    res.sign = x.sign;
    int n = x.nbytes;
    int k = 0;
    int mem = 0;
    res.nbytes = n;
    res.data = new BYTE[n + 1];
    res.data[n] = 0;
    for (int i = 0; i < n; i++)
    {
        k = x.data[i] * num + mem;
        if (k > 255)
        {
            mem = k / 256;
            k = k % 256;
        }
        else
            mem = 0;
        res.data[i] = k;
    }
    if (mem > 0)
    {
        res.data[n] = mem;
        mem = 0;
        res.nbytes++;
    }
    return res;
}

bigint operator+(bigint x,bigint y)
{
    bigint res;
    if (x.sign == 0)
    {
        if (y.sign == 0)
        {
            copy(res, BigintAddition(x, y));
            res.sign = 0;
        }
        else
        {
            if ((x > y) != -1)
            {
                copy(res, BigintSubstraction(x, y));
                res.sign = 0;
            }
            else
            {
                copy(res, BigintSubstraction(y, x));
                res.sign = 1;
            }
        }
    }
    else
    {
        if (y.sign == 0)
        {
            if ((x > y))
            {
                copy(res,BigintSubstraction(x, y));
                res.sign = 1;
            }
            else
            {
                copy(res,BigintSubstraction(x, y));
                res.sign = 0;
            }
        }
        else
        {
            copy(res,BigintAddition(x, y));
            res.sign = 1;
        }
    }
    return res;
}

bigint operator-(bigint x,bigint y)
{   
    bigint res;
    if ((x > y) == 0)
    {
        res.nbytes = 1;
        res.data = new BYTE[1];
        res.sign = 0;
        res.data[0] = 0;
        return res;
    }
    if ((x > y) == 1)
    {
        copy(res, BigintSubstraction(x, y));
        res.sign = 0;
    }
    else
    {
        copy(res, BigintSubstraction(y, x));
        res.sign = 1;
    }
    return res;
}

bigint operator*(bigint x,bigint y)
{
    bigint res, tmp;
    int nx = x.nbytes;
    int ny = y.nbytes;
    int n = nx + ny;
    res.data = new BYTE[n + 1];
    tmp.data = new BYTE[n + 1];
    res.nbytes = n;
    tmp.nbytes = n;
    int mem = 0;
    for (int i = 0; i <= n; i++)
    {
        res.data[i] = 0;
        tmp.data[i] = 0;
    }
    for (int i = 0; i < ny; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (j < i)
                tmp.data[j] = 0;
            if (j >= i && j < nx + i)
            {
                tmp.data[j] = (x.data[j - i] * y.data[i] + mem);
                if (x.data[j - i] * y.data[i] + mem > 255)
                {
                    mem = (x.data[j - i] * y.data[i] + mem) / 256;
                }
                else
                    mem = 0;
            }
            else if (mem > 0 && j == nx + i)
            {
                tmp.data[j] = mem;
                mem = 0;
            }
            else
                tmp.data[j] = 0;
        }
        res = res + tmp;
    }
    if (x.sign != y.sign)
        res.sign = 1;
    freedata(tmp);
    return res;
}

bigint BigintDivision(const bigint &x,int num)
{
    bigint res;
    bigint tmp_x;
    tmp_x = x;
    int n = tmp_x.nbytes;
    res.nbytes = n;
    res.data = new BYTE[n];
    res.sign = x.sign;
    int tmp = 0;
    int mem = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        tmp = (tmp_x.data[i] + mem*256) / num;
        mem = (tmp_x.data[i] + mem*256) % num;
        res.data[i] = tmp;
    }
    freedata(tmp_x);
    return res;
}

bigint operator/(const bigint &x,const bigint &y)
{
    bigint carry, count;
    copy(count, ShiftRight(count));
    copy(carry, ShiftRight(carry));
    carry.data[0] = 0;
    count.data[0] = 1;  
    bigint tmp_x, tmp_y;
    if ((x > y) != -1)
    {
        tmp_x = x;
        tmp_y = y;
        do
        {
            copy(carry, carry + count);
            copy(tmp_x, tmp_x - tmp_y);
            copy(tmp_y, BigintMultiplication(tmp_y, 2));
            copy(count, BigintMultiplication(count, 2));
        } while ((tmp_x > tmp_y) != -1);
        do
        {
            copy(tmp_y, BigintDivision(tmp_y, 2));
            copy(count, BigintDivision(count, 2));
            if ((tmp_x > tmp_y) != -1)
            {
                copy(carry, carry + count);
                copy(tmp_x, tmp_x - tmp_y);
            }
        } while ((tmp_x > y) != -1);
    }
    freedata(tmp_x);
    freedata(tmp_y);
    freedata(count);
    return carry;
}

bigint operator%(const bigint &x,const bigint &y)
{
    bigint res;
    bigint tmp;
    bigint tmp_x;
    bigint tmp_y;
    tmp_x = x;
    tmp_y = y;
    copy(tmp, tmp_x / tmp_y);
    copy(tmp, tmp * tmp_y);
    copy(tmp, tmp_x - tmp);
    res = tmp;
    freedata(tmp);
    freedata(tmp_x);
    freedata(tmp_y);
    return res;
}

bool BigintIsNonZero(bigint x)
{
    int n = x.nbytes;
    for (int i = 0; i < n; i++)
        if (x.data[i] != 0)
            return 1;
    return 0;
}

string BigintToDecimal(const bigint &x)
{
    string t = "";
    bigint tmp_x1;
    tmp_x1 = x;
    bigint y;
    y.data = new BYTE[1];
    y.data[0] = 10;
    y.nbytes = 1;
    y.sign = 0;
    while (BigintIsNonZero(tmp_x1))
    {
        bigint carry;
        copy(carry, (tmp_x1 % y));
        t += carry.data[0] + '0';
        copy(tmp_x1, tmp_x1 / y);
        freedata(carry);
    }
    reverse(t.begin(), t.end());
    freedata(y);
    freedata(tmp_x1);
    return t;
}