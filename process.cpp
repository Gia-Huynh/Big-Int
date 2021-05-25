#include"process.h"

void freedata(bigint x)
{
    if (x.data != NULL)
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

void reAllocation(bigint& x)
{
    x.nbytes = countbytes(BigintToDecimal(x));
};
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
        res.data[i + 1] = x.data[i];
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


int operator>(bigint x, bigint y)
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

    for (int i = n - 1; i >= 0; i--)
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

bigint BigintAddition(bigint x, bigint y)
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

bigint BigintSubstraction(bigint x, bigint y)
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
bigint BigintMultiplication(bigint x, int num)
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

bigint BigintMod(const bigint& x, int num)
{
    bigint res;
    bigint tmp;
    copy(tmp, BigintDivision(x, 10));
    copy(res, BigintMultiplication(tmp, 10));
    copy(res, x - res);
    freedata(tmp);
    return res;
}

bigint operator+(const bigint& x, const bigint& y)
{
    bigint res;
    bigint tmp_x;
    bigint tmp_y;
    tmp_x = x;
    tmp_y = y;
    if (tmp_x.sign == 0)
    {
        if (tmp_y.sign == 0)
        {
            copy(res, BigintAddition(tmp_x, tmp_y));
            res.sign = 0;
        }
        else
        {
            if ((tmp_x > tmp_y) != -1)
            {
                copy(res, BigintSubstraction(tmp_x, tmp_y));
                res.sign = 0;
            }
            else
            {
                copy(res, BigintSubstraction(tmp_y, tmp_x));
                res.sign = 1;
            }
        }
    }
    else
    {
        if (tmp_y.sign == 0)
        {
            if ((tmp_x > tmp_y) != -1)
            {
                copy(res, BigintSubstraction(tmp_x, tmp_y));
                res.sign = 1;
            }
            else
            {
                copy(res, BigintSubstraction(tmp_y, tmp_x));
                res.sign = 0;
            }
        }
        else
        {
            copy(res, BigintAddition(tmp_x, tmp_y));
            res.sign = 1;
        }
    }
    freedata(tmp_x);
    freedata(tmp_y);
    return res;
}

bigint operator-(const bigint& x, const bigint& y)
{
    bigint res;
    if (x.sign == y.sign)
    {
        if ((x > y) == 0)
        {
            copy(res, ShiftRight(res));
            return res;
        }
    }
    bigint tmp_y;
    bigint tmp_x;
    tmp_x = x;
    tmp_y = y;
    tmp_y.sign = 1 - tmp_y.sign;
    copy(res, tmp_x + tmp_y);
    freedata(tmp_x);
    freedata(tmp_y);
    return res;
}

bigint operator*(const bigint& x, const bigint& y)
{
    bigint res, tmp;
    bigint tmp_x;
    bigint tmp_y;
    tmp_x = x;
    tmp_y = y;
    int nx = tmp_x.nbytes;
    int ny = tmp_y.nbytes;
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
                if (tmp_x.data[j - i] * tmp_y.data[i] + mem > 255)
                {
                    mem = (tmp_x.data[j - i] * y.data[i] + mem) / 256;
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
        copy(res, res + tmp);
    }
    if (tmp_x.sign != tmp_y.sign)
        res.sign = 1;
    freedata(tmp);
    freedata(tmp_x);
    freedata(tmp_y);
    return res;
}

bigint BigintDivision(const bigint& x, int num)
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
        tmp = (tmp_x.data[i] + mem * 256) / num;
        mem = (tmp_x.data[i] + mem * 256) % num;
        res.data[i] = tmp;
    }
    freedata(tmp_x);
    return res;
}

Bigint BigintModulo(const bigint& x, const bigint& y)
{
    bigint res;
    bigint tmp_x;
    bigint tmp_y;
    if ((x > y) != -1)
    {
        tmp_x = x;
        tmp_y = y;
        do
        {
            copy(tmp_x, tmp_x - tmp_y);
            copy(tmp_y, tmp_y << 1);
        } while ((tmp_x > tmp_y) != -1);
        do
        {
            copy(tmp_y, tmp_y >> 1);
            if ((tmp_x > tmp_y) != -1)
            {
                copy(tmp_x, tmp_x - tmp_y);
            }
        } while ((tmp_x > y) != -1);
    }
    else
        tmp_x = x;

    res = tmp_x;
    freedata(tmp_x);
    freedata(tmp_y);
    return res;
}

bigint operator/(const bigint& x, const bigint& y)
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
        tmp_x.sign = 0;
        tmp_y.sign = 0;
        do
        {
            copy(carry, carry + count);
            copy(tmp_x, tmp_x - tmp_y);
            copy(tmp_y, tmp_y << 1);
            copy(count, count << 1);
        } while ((tmp_x > tmp_y) != -1);
        do
        {
            copy(tmp_y, tmp_y >> 1);
            copy(count, count >> 1);
            if ((tmp_x > tmp_y) != -1)
            {
                copy(carry, carry + count);
                copy(tmp_x, tmp_x - tmp_y);
            }
        } while ((tmp_x > y) != -1);
    }
    else
    {
        freedata(tmp_x);
        freedata(tmp_y);
        return carry;
    }
    if (x.sign != y.sign)
        carry.sign = 1;
    freedata(tmp_x);
    freedata(tmp_y);
    freedata(count);
    return carry;
}

bigint operator%(const bigint& x, const bigint& y)
{
    bigint res;
    if (x.sign == y.sign)
    {
        if ((x > y) == 0)
        {
            copy(res, ShiftRight(res));
            return res;
        }
    }
    bigint tmp_x;
    bigint tmp_y;
    tmp_x = x;
    tmp_y = y;
    if (tmp_x.sign == 0)
    {
        if (tmp_y.sign == 0)
        {
            copy(res, BigintModulo(tmp_x, tmp_y));
        }
        else
        {
            tmp_y.sign = 0;
            copy(res, BigintModulo(tmp_x, tmp_y));
            copy(res, res - tmp_y);
        }
    }
    else
    {
        if (tmp_y.sign == 0)
        {
            tmp_x.sign = 0;
            copy(res, BigintModulo(tmp_x, tmp_y));
            copy(res, tmp_y - res);
        }
        else
        {
            tmp_x.sign = 0;
            tmp_y.sign = 0;
            copy(res, BigintModulo(tmp_x, tmp_y));
            res.sign = 1;
        }
    }
    freedata(tmp_x);
    freedata(tmp_y);
    reAllocation(res);
    return res;
}

bigint power(const bigint& x, const bigint& y) // x^y
{
    bigint res;
    bigint sum;
    bigint tmp_y;
    bigint tmp;
    tmp_y = y;
    res = x;
    copy(sum, ShiftRight(sum));
    copy(tmp, ShiftRight(tmp));
    sum.data[0] = 1;
    tmp.data[0] = 1;
    while ((tmp_y > tmp))
    {
        if (tmp_y.data[tmp_y.nbytes - 1] % 2 == 1)
        {
            copy(sum, sum * res);
        }
        copy(res, res * res);
        copy(tmp_y, tmp_y >> 1);
    }
    copy(res, sum * res);
    freedata(sum);
    freedata(tmp);
    freedata(tmp_y);
    return res;
}

bigint operator&(const bigint& x, const bigint& y)
{
    bigint res;
    if (x.sign == 0 && y.sign == 0)
    {
        bigint tmp_x;
        bigint tmp_y;
        tmp_x = x;
        tmp_y = y;
        int nx = tmp_x.nbytes;
        int ny = tmp_y.nbytes;
        int n = (nx > ny) ? nx : ny;
        while (nx < n)
        {
            copy(tmp_x, ShiftRight(tmp_x));
            nx++;
        }
        while (ny < n)
        {
            copy(tmp_x, ShiftRight(tmp_y));
            ny++;
        }
        res.nbytes = n;
        res.data = new BYTE[n];
        for (int i = 0; i < n; i++)
        {
            res.data[i] = (tmp_x.data[i] & tmp_y.data[i]);
        }
        freedata(tmp_x);
        freedata(tmp_y);
        return res;
    }
    else
    {
        string p, q;
        string r = "";
        p = BigintToBinary(x);
        q = BigintToBinary(y);
        int nx = p.length();
        int ny = q.length();
        int n = (nx > ny) ? nx : ny;
        int i = nx;
        int j = ny;
        reverse(p.begin(), p.end());
        reverse(q.begin(), q.end());
        while (i < n)
        {
            p += p[nx - 1];
            i++;
        }
        while (j < n)
        {
            q += q[ny - 1];
            j++;
        }
        for (int i = 0; i < n; i++)
        {
            if (p[i] == q[i] && p[i] == '1')
            {
                r += "1";
            }
            else
                r += "0";
        }
        reverse(r.begin(), r.end());
        BinaryToBigint(res, r);
    }
    return res;
}

bigint operator|(const bigint& x, const bigint& y)
{
    bigint res;
    if (x.sign == 0 && y.sign == 0)
    {
        bigint tmp_x;
        bigint tmp_y;
        tmp_x = x;
        tmp_y = y;
        int nx = tmp_x.nbytes;
        int ny = tmp_y.nbytes;
        int n = (nx > ny) ? nx : ny;
        while (nx < n)
        {
            copy(tmp_x, ShiftRight(tmp_x));
            nx++;
        }
        while (ny < n)
        {
            copy(tmp_x, ShiftRight(tmp_y));
            ny++;
        }
        res.nbytes = n;
        res.data = new BYTE[n];
        for (int i = 0; i < n; i++)
        {
            res.data[i] = (tmp_x.data[i] | tmp_y.data[i]);
        }
        freedata(tmp_x);
        freedata(tmp_y);
        return res;
    }
    else
    {
        string p, q;
        string r = "";
        p = BigintToBinary(x);
        q = BigintToBinary(y);
        int nx = p.length();
        int ny = q.length();
        int n = (nx > ny) ? nx : ny;
        int i = nx;
        int j = ny;
        reverse(p.begin(), p.end());
        reverse(q.begin(), q.end());
        while (i < n)
        {
            p += p[nx - 1];
            i++;
        }
        while (j < n)
        {
            q += q[ny - 1];
            j++;
        }
        for (int i = 0; i < n; i++)
        {
            if (p[i] == q[i] && p[i] == '0')
            {
                r += "0";
            }
            else
                r += "1";
        }
        reverse(r.begin(), r.end());
        BinaryToBigint(res, r);
    }
    return res;
}

bigint operator^(const bigint& x, const bigint& y)
{
    bigint res;
    if (x.sign == 0 && y.sign == 0)
    {
        bigint tmp_x;
        bigint tmp_y;
        tmp_x = x;
        tmp_y = y;
        int nx = tmp_x.nbytes;
        int ny = tmp_y.nbytes;
        int n = (nx > ny) ? nx : ny;
        while (nx < n)
        {
            copy(tmp_x, ShiftRight(tmp_x));
            nx++;
        }
        while (ny < n)
        {
            copy(tmp_x, ShiftRight(tmp_y));
            ny++;
        }
        res.nbytes = n;
        res.data = new BYTE[n];
        for (int i = 0; i < n; i++)
        {
            res.data[i] = (tmp_x.data[i] ^ tmp_y.data[i]);
        }
        freedata(tmp_x);
        freedata(tmp_y);
        return res;
    }
    else
    {
        string p, q;
        string r = "";
        p = BigintToBinary(x);
        q = BigintToBinary(y);
        int nx = p.length();
        int ny = q.length();
        int n = (nx > ny) ? nx : ny;
        int i = nx;
        int j = ny;
        reverse(p.begin(), p.end());
        reverse(q.begin(), q.end());
        while (i < n)
        {
            p += p[nx - 1];
            i++;
        }
        while (j < n)
        {
            q += q[ny - 1];
            j++;
        }
        for (int i = 0; i < n; i++)
        {
            if (p[i] == q[i])
            {
                r += "0";
            }
            else
                r += "1";
        }
        reverse(r.begin(), r.end());
        BinaryToBigint(res, r);
    }
    return res;
}

bigint operator~(const bigint& x)
{
    bigint res;
    res.sign = 1 - x.sign;
    res.nbytes = x.nbytes;
    res.data = new BYTE[res.nbytes];
    for (int i = 0; i < res.nbytes; i++)
    {
        res.data[i] = x.data[i];
    }
    bigint tmp;
    tmp.sign = 1;
    tmp.nbytes = 1;
    tmp.data = new BYTE[1];
    tmp.data[0] = 1;
    copy(res, res + tmp);
    freedata(tmp);
    return res;
}

bigint square(const bigint& x)
{
    bigint res;
    copy(res, res * res);
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

string BigintToDecimal(const bigint& x)
{
    string t = "";
    bigint tmp_x1;
    tmp_x1 = x;
    bigint carry;
    while (BigintIsNonZero(tmp_x1))
    {
        copy(carry, BigintMod(tmp_x1, 10));
        t += carry.data[0] + '0';
        copy(tmp_x1, BigintDivision(tmp_x1, 10));
    }
    if (x.sign == 1)
        t += "-";
    reverse(t.begin(), t.end());
    freedata(tmp_x1);
    freedata(carry);
    if (t.length() == 0)
        return "0";
    return t;
}

int countspace(string t)
{
    int s = 0;
    int n = t.length();
    for (int i = 0; i < n; i++)
    {
        if (t[i] == ' ')
            s++;
    }
    return s;
}

bigint Abs(const bigint& x)
{
    bigint res;
    res = x;
    if (res.sign == 1)
    {
        res.sign = 0;
    }
    return res;
}

bigint operator<<(const bigint& x, int cnt)
{
    bigint res;
    bigint tmp_x;
    tmp_x = x;
    for (int i = 0; i < cnt; i++)
    {
        int k = 0;
        for (int j = 0; j < tmp_x.nbytes; j++)
        {
            if (tmp_x.data[j] >= 128)
            {
                tmp_x.data[j] = (tmp_x.data[j] << 1) + k;
                k = 1;
            }
            else
            {
                tmp_x.data[j] = (tmp_x.data[j] << 1) + k;
                k = 0;
            }
        }
        if (k == 1)
        {
            copy(tmp_x, ShiftRight(tmp_x));
            tmp_x.data[tmp_x.nbytes - 1] = 1;
        }
    }
    res = tmp_x;
    freedata(tmp_x);
    return res;
}

bigint operator>>(const bigint& x, int cnt)
{
    bigint res;
    bigint tmp_x;
    tmp_x = x;
    for (int i = 0; i < cnt; i++)
    {
        int k = 0;
        for (int j = tmp_x.nbytes - 1; j >= 0; j--)
        {
            if (tmp_x.data[j] % 2 == 1)
            {
                tmp_x.data[j] = (tmp_x.data[j] >> 1) + k;
                k = 128;
            }
            else
            {
                tmp_x.data[j] = (tmp_x.data[j] >> 1) + k;
                k = 0;
            }
        }
    }
    res = tmp_x;
    freedata(tmp_x);
    return res;
}

bigint min(const bigint& x, const bigint& y)
{
    bigint res;
    bigint tmp_x;
    bigint tmp_y;
    tmp_x = x;
    tmp_y = y;
    if ((tmp_x > tmp_y) != -1)
    {
        res = y;
        return res;
    }
    else
    {
        res = x;
        return res;
    }
    freedata(tmp_x);
    freedata(tmp_y);
    return res;
}

bigint max(const bigint& x, const bigint& y)
{
    bigint res;
    bigint tmp_x;
    bigint tmp_y;
    tmp_x = x;
    tmp_y = y;
    if ((tmp_x > tmp_y) != -1)
    {
        res = x;
        return res;
    }
    else
    {
        res = y;
        return res;
    }
    freedata(tmp_x);
    freedata(tmp_y);
    return res;
}

int digits(const bigint& x)
{
    string t;
    t = BigintToDecimal(x);
    int n = t.length();
    return n;
}

bool isEven(const bigint& x)
{
    if (x.data[0] % 2 == 0)
    {
        return 1;
    }
    return 0;
}
//////////////////////////////////////////////////
// ********** P R I M E _ T E S T ****************
//////////////////////////////////////////////////
void copy_2(bigint& x, bigint& y)
{
    x.nbytes = y.nbytes;
    x.data = y.data;
    x.sign = y.sign;
}
void DecimalToBigint(bigint& x, int s_int)
{
    string s = to_string(s_int);
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
/// <summary>
/// Display BigInt 
/// </summary>
/// <param name="x"></param>
void DpBigInt(bigint x)
{
    int nx = x.nbytes;
    for (int i = 0; i < nx; i++)
    {
        printf("%d", x.data[i]-'0');
    };
};
bigint DecToBigint_2(int s_int)
{
    bigint x;
    string s = to_string(s_int);
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
    return x;
}

int operator== (const bigint x, const bigint y)
{
    int nx = x.nbytes;
    int ny = y.nbytes;
    if (nx != ny) return 0;
    for (int i = 0; i < nx; i++)
    {
        if (x.data[i] != y.data[i]) return 0;
    };
    return 1;
};

int operator== (const bigint x, const int y_int)
{
    Bigint y = DecToBigint_2(y_int);
    int nx = x.nbytes;
    int ny = y.nbytes;
    if (nx != ny) return 0;
    for (int i = 0; i < nx; i++)
    {
        if (x.data[i] != y.data[i]) return 0;
    };
    return 1;
};
int operator>(bigint x, int y)
{
    bigint tmp_x;
    bigint tmp_y;
    tmp_x = x;
    DecimalToBigint(tmp_y, y);
    int nx = x.nbytes;
    int ny = tmp_y.nbytes;
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

    for (int i = n - 1; i >= 0; i--)
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
bigint operator%(const bigint& x, const int& y)
{   
    bigint tmp_y;
    DecimalToBigint(tmp_y, y);
    bigint res;
    copy(res, x % tmp_y);
    freedata(tmp_y);
    return res;
}

bigint min (bigint x, bigint y)
{
    if (x > y) return y; else return x;
};
Bigint powermod(Bigint base_int, Bigint exponent_gay, Bigint modulus) {
    Bigint zero; DecimalToBigint(zero, 0);
    Bigint one; DecimalToBigint(one, 1);
    Bigint two; DecimalToBigint(two, 2);
    bigint exponent;
    copy(exponent, exponent_gay + zero);
    //cout << "\nPower mod: " << BigintToDecimal(base_int) << "^" << BigintToDecimal(exponent) << " mod " << BigintToDecimal(modulus);
    Bigint base;    copy(base, base_int + zero);
    if ((base > 1 == -1) || (exponent > 0 == -1) || modulus > 1 == -1)
    {
        cout << "\nError in power mod\n";
        Bigint nega_one; DecimalToBigint(nega_one, -1);
        return nega_one;
    }

    Bigint result; 
    DecimalToBigint(result, 1);
    //bool exponent_mod;
    bigint modHalf;
    bigint temp;
    copy(modHalf, modulus >> 1);
    while (exponent > 0) {
        //copy(exponent_mod, exponent % 2);
        //exponent_mod = isEven(exponent);
        //cout << "\nexponent_mod: " << BigintToDecimal(exponent_mod) << " " << exponent_mod.nbytes;
        //cout << "\nDecBigInt: " << BigintToDecimal(DecToBigint_2(1)) << " " << DecToBigint_2(1).nbytes;
        if (isEven(exponent) == 0) {
            //cout << "\nmodulos ";
            //cout << BigintToDecimal(result) << "* " << BigintToDecimal(base) << "\n";
            if (result > modHalf == 1)  copy(result, result - modulus);
            if (base > modHalf == 1)    copy(base, base - modulus);
            copy(result, (result * base));
            if (result > modulus == 1) 
            { 
                copy(result, result % modulus);
                copy(result, result * one);
                copy(result, result - zero);
            };
            copy(exponent, exponent - one);
        }
        if (base > modHalf == 1)    copy(base, base - modulus);
        copy(base, base * base);

        if (base > modulus == 1) 
        { 
            copy(base, base % modulus);
            copy(base, base * one);
            copy(base, base - zero);
        }
        copy(exponent, exponent >> 1);
    };
    freedata(zero);    freedata(one);    freedata(two);    freedata(exponent);    freedata(base);    freedata(modHalf);    freedata(temp);
    return result;
}
Bigint powermod(int base_int, Bigint exponent_gay, bigint modulus)
{
    Bigint based;
    DecimalToBigint(based, base_int);
    return powermod(based, exponent_gay, modulus);
}
/// <summary>
/// Miller Rabin with base 2
/// </summary>
/// <param name="n"></param>
/// <returns></returns>
int MillerRabin(Bigint n)
{
    Bigint zero; DecimalToBigint(zero, 0);
    Bigint negaOne; DecimalToBigint(negaOne, -1);
    Bigint one; DecimalToBigint(one, 1);
    Bigint two; DecimalToBigint(two, 2);
    if ((n > DecToBigint_2(3) == -1) || (isEven(n)))
    {
        printf("Assertion Fail, PrimeTest, N<3 or N chia het cho 2\n");
        return 0;
    };
    Bigint d;
    copy (d, n - one);
    //cout << "\nOG D: " << BigintToDecimal(d);
    //D = 2^x * d;
    int s = 0;
    Bigint pwm_result;
    Bigint temp_d;

    copy(d, d / two);
    while (isEven(d) == 1)
    {
        //D = 2^(x-1) * d
        //copy(temp_d, d + zero);
        copy(pwm_result, powermod(2, d, n));
        if ((pwm_result > negaOne) == 0) {return 1;};
        copy(pwm_result, pwm_result - n);
        if ((pwm_result > negaOne) == 0) {return 1;};

        if (isEven(d) == 0) break;
        copy(d, d / two);
    };
    //D = 2^0 * d
    //cout << "MILLER RABIN DONE?";
    copy(pwm_result, powermod(2, d, n));
    //cout << "\nResult LAST D: " << BigintToDecimal(pwm_result);
    if (pwm_result > one == 0) return 1;
    if (pwm_result > negaOne == 0) return 1;
    copy(temp_d, n - one);
    if (pwm_result > temp_d == 0) return 1;

    freedata(one);    freedata(zero);    freedata(negaOne);    freedata(two);    freedata(d);    freedata(pwm_result);    freedata(temp_d);    
    return 0;
};
int jacobi_cpp(Bigint &k, Bigint &n)
// N VOI K BI SWAP BEN TRONG FUNCTION JACOBI
{
    Bigint r;
    Bigint temp;
    if ((k > 0 != 1) || (isEven (k)))
        // neu k <= 0 hay k%2 = 0
    {
        printf("ERROR IN JACOBI CALCULATION, ASSERTION K FAILED"); return 2;
    };
    copy(n, n % k);
    int t = 1;
    bigint zero;
    DecimalToBigint(zero, 0);
    int count = 0;
    while (n > 0 != 0)
    {
        while (isEven (n))
        {
            copy(n, n / DecToBigint_2 (2));
            //r = k % 8;
            copy(r, k % 8);
            if ((r == 3) or (r == 5))
            {
                t = -1 * t;
            }
        };
        //swap(n, k);
        copy(temp, n + zero);
        copy(n, k + zero);
        copy(k, temp + zero);
        copy(r, n % 4);
        copy(temp, k % 4);
        //if ((n % 4 == 3) && (k % 4 == 3)) t = -1 * t;
        if ((r == 3) && (temp == 3)) t = -1 * t;
        //n = n % k;
        copy(n, n % k);
        count = count + 1;
        if (count == 10000) return 2;
    };
    freedata(temp);
    freedata(r);
    if (k == 1) return t;
    else return 0;
};


bigint lucas_mod(char mode, bigint& n, bigint& p, bigint& q, bigint D, bigint x)
{
    //https://en.wikipedia.org/wiki/Lucas_pseudoprime#Implementing_a_Lucas_probable_prime_test
    string a = BigintToNosignBinary(n);
    long a_length = a.length();
    if (p > x == 1) copy(p, p % x);
    if (q > x == 1) copy(q, q % x);

    bigint* lucasU;
    lucasU = new bigint[2];
    bigint* lucasV;
    lucasV = new bigint[2];
        DecimalToBigint(*lucasU, 0);
        DecimalToBigint(*(lucasU + 1), 1);
    
        DecimalToBigint(*lucasV, 2);
        DecimalToBigint(*(lucasV + 1), BigintToDecimal(p));
    bigint m;    DecimalToBigint(m, 2);
    bigint gay;
    bigint two; DecimalToBigint(two, 2);
    bigint one; DecimalToBigint(one, 1);
    bigint zero; DecimalToBigint(zero, 0);
    if (mode == 'u')
    {
        if (n == 0) return *(lucasU); else if (n == 1) return *(lucasU + 1); 
    }
        else if (mode == 'v')
    {
            if (n == 0) return *(lucasV); else if (n == 1) return *(lucasV + 1); 
    }
    long long b = 1;
    for (int i = 1; i < a_length; i++)
    {
        //copy (U+1) voi (V+1) sang backup la (U) va (V)
        copy(*lucasU, *(lucasU + 1) + zero);
        copy(*lucasV, *(lucasV + 1) + zero);
        //*(U+1) = *(U+1) * *(V);
        //U(2k) = U(k) * V(k);
        copy(*(lucasU + 1), *(lucasU + 1) * (*(lucasV)));
        copy(*(lucasU + 1), *(lucasU + 1) % x);

        //V(2k) = ( V(k)^2 + D * U(k)^2 ) / 2;

        //*(V+1) = *(V+1) * *(V+1);
        copy(*(lucasV + 1), *(lucasV + 1) * (*(lucasV + 1)));
        //V bak = U^2 * D;
        copy(*(lucasV), *(lucasU) * (*(lucasU)));
        copy(*(lucasV), *(lucasV) * D);
        copy(*(lucasV + 1), *(lucasV + 1) + (*(lucasV)));
        if (isEven(*(lucasV + 1)) == 0)
        {
            copy(*(lucasV + 1), *(lucasV + 1) + x);
        };
        copy(*(lucasV + 1), *(lucasV + 1) / two);
        copy(*(lucasV + 1), *(lucasV + 1) % x);
        
        b = b * 2;
        if (a[i] == '1')
        {
            b = b + 1;
            //D * U(2k)
            copy(*(lucasU), *(lucasU + 1) * D);

            //U(k+1) {
            copy(*(lucasU + 1), *(lucasU + 1) * p);
            copy(gay, *(lucasU + 1) + *(lucasV + 1));
            copy(*(lucasU + 1), *(lucasV + 1) + *(lucasU + 1));
            if (isEven(*(lucasU + 1)) == 0)
            {
                copy(*(lucasU + 1), *(lucasU + 1) + x);
            }; 
            copy(*(lucasU + 1), *(lucasU + 1) / two);
            copy(gay, *(lucasU + 1) / two);
            //} U(k+1)
            
            //V (k+1) {
            copy(*(lucasV + 1), *(lucasV + 1) * p);
            copy(*(lucasV + 1), *(lucasV + 1) % x);
            copy(*(lucasV + 1), *(lucasV + 1) + *(lucasU));
            copy(*(lucasV + 1), *(lucasV + 1) % x);
            if (isEven(*(lucasV + 1)) == 0)
            {
                copy(*(lucasV + 1), *(lucasV + 1) + x);
            };
            copy(*(lucasV + 1), *(lucasV + 1) / two);
            //} V(k+1)


            if (*(lucasU + 1) > x == 1) copy(*(lucasU + 1), *(lucasU + 1) % x);
            if (*(lucasV + 1) > x == 1) copy(*(lucasV + 1), *(lucasV + 1) % x);
        }; 

    };

    if (mode == 'u')
    {
        return *(lucasU + 1);
    }
    else {
        return *(lucasV + 1);
    };
};
bool Lucas_test(bigint &x, bigint &D, bigint &p, bigint &q)
{
    Bigint d;
    copy(d, x + DecToBigint_2(1));
    //D = 2^x * d;
    int s = 0;
    Bigint zero;
    DecimalToBigint(zero, 0);
    Bigint two;
    DecimalToBigint(two, 2);
    Bigint pwm_result;
    Bigint temp_d;

    copy(d, d >> 1);
    while (true)
    {
        //D = 2^(x-1) * d
        //lucas_mod_old('v', d, p, q, x);
        copy(pwm_result, lucas_mod('v', d, p, q, D, x));
        copy(pwm_result, pwm_result % x);
        
        if ((pwm_result > zero) == 0) return 1;
        if (isEven(d) == 0) break;
        copy(d, d >> 1);
    } ;
    //D = 2^0 * d
    //lucas_mod_old('u', d, p, q, x);
    copy(pwm_result, lucas_mod('u', d, p, q, D, x));
    copy(pwm_result, pwm_result % x);
    if ((pwm_result > zero) == 0) return 1;
    return 0;
};
bool PrimeCheck(const bigint x)
{
    bigint zero;
    bigint modResult;
    DecimalToBigint(zero, 0);
    bigint one;
    DecimalToBigint(one, 1);
    bigint two;
    DecimalToBigint(two, 2);
    if (x > two == 0)
    {
        freedata(zero);
        freedata(modResult);
        printf("\nSo nguyen to\n");
        return 1;
    };
    
    //Early detection, i = 2 ---> 100 de kiem tra prime nho
    bigint temp;
    for (int i = 2; i < 100; i++)
    {
        DecimalToBigint(temp, i);
        copy(modResult, x % temp);
        //copy(modResult, x % i);
        if (modResult > zero == 0)
        {
            if (x == temp) {
                break;
            };
            printf("\nKHONG PHAI PRIME, chia het cho %d\n", i);
            return 0;
        };
    };
    //Miller Rabin
    //cout << "Miller\n";
    if (MillerRabin(x) != 1) return 0;
    //cout << "Jacobi\n";
    //Jacobi symbol calculation
    copy(modResult, DecToBigint_2(5));
    int Jacobi;
    int sign = 1;
    Bigint k;
    Bigint n;
    Jacobi = 1;
    while (true)
    {
        copy(k, modResult * one);
        DecimalToBigint(n, BigintToDecimal(x));
        // N VOI K BI SWAP BEN TRONG FUNCTION JACOBI
        Jacobi = jacobi_cpp(n, k);
        if (Jacobi == -1) 
        { 
            break; 
        };
        if (Jacobi == 2) return 0;
        copy(modResult, modResult + DecToBigint_2(2 * sign));
        copy(modResult, modResult * DecToBigint_2(-1));
        sign = sign * -1;
    };
    //modResult la D Set P = 1 and Q = (1 - D)/4
    //Perform a strong Lucas probable prime test on n using parameters D, P, and Q.
    //cout << "Lucas\n";
    bigint P;
    bigint Q;
    DecimalToBigint(P, 1);
    copy(Q, one - modResult);
    copy (Q, Q >> 2);
    DecimalToBigint(Q, BigintToDecimal (Q));
    copy(n, x + zero);
    if (Lucas_test(n, modResult, P, Q) == 1)
    {
        freedata(zero);        freedata(one);        freedata(two);        freedata(k);        freedata(n);        freedata(modResult);
        printf("So nguyen to (probably)\n");
        return 1;
    };
    freedata(zero);        freedata(one);        freedata(two);        freedata(k);        freedata(n);        freedata(modResult);
    return 0;
};
