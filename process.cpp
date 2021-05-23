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
/// <summary>
/// Shift right, "1011" ~> "01011"
/// </summary>
/// <param name="x"></param>
/// <returns></returns>
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
/// <summary>
/// Copy y sang x
/// </summary>
/// <param name="x"> x </param>
/// <param name="y"> x </param>
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

/// <summary>
/// 1 > ; -1 < ; 0 =
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <returns></returns>
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
/// <summary>
/// X - Y
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <returns></returns>
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

bigint BigintMod(const bigint &x, int num)
{
    bigint res;
    bigint tmp;
    copy(tmp, BigintDivision(x, 10));
    copy(res, BigintMultiplication(tmp, 10));
    copy(res, x-res);
    freedata(tmp);
    return res;
}


bigint operator+(bigint x, bigint y)
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
            if ((x > y) != -1)
            {
                copy(res, BigintSubstraction(x, y));
                res.sign = 1;
            }
            else
            {
                copy(res, BigintSubstraction(y, x));
                res.sign = 0;
            }
        }
        else
        {
            copy(res, BigintAddition(x, y));
            res.sign = 1;
        }
    }
    return res;
}
bigint operator-(bigint x, bigint y)
{
    bigint res;
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
        //res = res + tmp;
        copy(res, res + tmp);
    }
    if (x.sign != y.sign)
        res.sign = 1;
    freedata(tmp); 
   // DecimalToBigint(res, BigintToDecimal(res));
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


/*bigint operator%(const bigint &x,const bigint &y)
{
    bigint res;
    bigint tmp;
    bigint tmp_x;
    bigint tmp_y;
    tmp_x = x;
    tmp_y = y;
    //cout << "\nx: " << BigintToDecimal(x);
    //cout << "\ny: " << BigintToDecimal(y);
    copy(tmp, tmp_x / tmp_y);
    copy(tmp, tmp * tmp_y);
    copy(tmp, tmp_x - tmp); 
    res = tmp;
    freedata(tmp);
    freedata(tmp_x);
    freedata(tmp_y);
    DecimalToBigint(res, BigintToDecimal(res));
    return res;
}*/
bigint BigintModulo(const bigint& x, const bigint& y)
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
            copy(tmp_y, BigintMultiplication(tmp_y, 2));
        } while ((tmp_x > tmp_y) != -1);
        do
        {
            copy(tmp_y, BigintDivision(tmp_y, 2));
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

string BigintToDecimal(const bigint &x)
{
    string t = "";
    bigint tmp_x1;
    tmp_x1 = x;
    bigint carry;
    while (BigintIsNonZero(tmp_x1))
    {
       
        copy(carry,BigintMod(tmp_x1 , 10));
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
// ********** P R I M E _ T E S T ***************

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
    bigint res;
    bigint tmp;
    bigint tmp_x;
    bigint tmp_y;
    tmp_x = x;
    DecimalToBigint(tmp_y, y);
    //tmp_y = y;
    copy(tmp, tmp_x / tmp_y);
    copy(tmp, tmp * tmp_y);
    copy(tmp, tmp_x - tmp);
    res = tmp;
    freedata(tmp);
    freedata(tmp_x);
    freedata(tmp_y);
    DecimalToBigint(res, BigintToDecimal(res));
    return res;
}

bigint min (bigint x, bigint y)
{
    if (x > y) return y; else return x;
};
Bigint powermod(int base_int, Bigint exponent_gay, Bigint modulus) {
    Bigint one; DecimalToBigint(one, 1);
    Bigint two; DecimalToBigint(two, 2);
    bigint exponent;
    copy(exponent, exponent_gay * one);
    cout << "\nPower mod: " << base_int << "^" << BigintToDecimal(exponent) << " mod " << BigintToDecimal(modulus);
    //cout << "\nbase_int:   " << base_int;
    //cout << "\nmodulus:   " << BigintToDecimal(modulus); //ok
    //cout << "\nexponent: " << BigintToDecimal(exponent); //ok
    Bigint base;
    DecimalToBigint(base, base_int);
    if ((base > 1 == -1) || (exponent > 0 == -1) || modulus > 1 == -1)
    {
        Bigint nega_one; DecimalToBigint(nega_one, -1);
        return nega_one;
    }

    Bigint result; 
    DecimalToBigint(result, 1);
    Bigint exponent_mod;

    DecimalToBigint(exponent_mod, 0);

    while (exponent > 0) {
        copy(exponent_mod, exponent % 2);
        //cout << "\nexponent_mod: " << BigintToDecimal(exponent_mod) << " " << exponent_mod.nbytes;
        //cout << "\nDecBigInt: " << BigintToDecimal(DecToBigint_2(1)) << " " << DecToBigint_2(1).nbytes;
        if (exponent_mod > one == 0) {
            //cout << "modulos";
            copy(result, (result * base));
            if (result > modulus == 1) copy(result, (result % modulus));
            copy(exponent, exponent - one);
        }
        //base = (base * base) % modulus;


        //cout << "\nbased:   " << BigintToDecimal(base);
        copy(base, base * base);

        if (base > modulus == 1) copy(base, base % modulus); // ok 
        //cout << "\n Bytes: " << base.nbytes;
        //cout << "\nbased:   " << BigintToDecimal(base);
        //cout << "\nresult:   " << BigintToDecimal(result); //ok
        //cout << "\nexponent: " << BigintToDecimal(exponent); //ok
        copy(exponent, exponent / two);
    };
    freedata(one);
    freedata(two);
    return result;
}
/// <summary>
/// Miller Rabin with base 2
/// </summary>
/// <param name="n"></param>
/// <returns></returns>
int PrimeTest(Bigint n)
{
    cout << "\nN: " << BigintToDecimal(n);
    if ((n > DecToBigint_2(3) == -1) || (n % 2 == DecToBigint_2(0)))
    {
        printf("Assertion Fail, PrimeTest, N<3 or N chia het cho 2\n");
        return 2;
    };
    Bigint d = n - DecToBigint_2(1);
    cout << "\nOG D: " << BigintToDecimal(d);
    //D = 2^x * d;
    int s = 0;
    Bigint zero; DecimalToBigint(zero, 0);
    Bigint negaOne; DecimalToBigint(negaOne, -1);
    Bigint one; DecimalToBigint(one, 1);
    Bigint two; DecimalToBigint(two, 2);
    Bigint pwm_result;
    Bigint temp_d;
    Bigint dModHai;

    copy(dModHai, d % 2);
    copy(d, d / two);
    while (dModHai > zero == 0)
    {
        //D = 2^(x-1) * d
        DecimalToBigint(temp_d, BigintToDecimal(d));
        copy(pwm_result, powermod(2, temp_d, n));
        copy(pwm_result, pwm_result - n);
        //cout << "\nd: " << BigintToDecimal(d);
        //cout << "\nN: " << BigintToDecimal(n);
        //cout << "\nResult: " << BigintToDecimal(pwm_result);
        if ((pwm_result > negaOne) == 0) return 1;

        copy(dModHai, d % 2);
        if (dModHai > zero != 0) break;
        copy(d, d / two);
        copy(dModHai, d % 2);
    };
    //D = 2^0 * d
    cout << "\nResult LAST D: " << BigintToDecimal(powermod(2, d, n));
    cout << "MILLER RABIN DONE?";
    if (powermod(2, d, n) > one == 0) return 1;
    return 0;
};

int jacobi_cpp(Bigint &k, Bigint &n)
// N VOI K BI SWAP BEN TRONG FUNCTION JACOBI
{
    //cout << "\nN: " << BigintToDecimal(n) << " K: " << BigintToDecimal(k);
    Bigint r;
    Bigint temp;
    copy(temp, k % 2);
    if ((k > 0 != 1) || (((temp) > 1) != 0))
        // neu k <= 0 hay k%2 = 0
    {
        printf("ERROR IN JACOBI CALCULATION, ASSERTION K FAILED"); return 2;
    };
    //n = n % k;
    copy(n, n % k);
    int t = 1;
    //while (n != 0)
    while (n > 0 != 0)
    {
        copy(temp, n % 2);
        //while (((n % 2) > 0) != 0)
        while ((temp > 0) == 0)
        {
            //cout << "\nN: " << BigintToDecimal(n) << " K: " << BigintToDecimal(k) << " Temp: " << BigintToDecimal(temp);
            copy(n, n / DecToBigint_2 (2));
            //r = k % 8;
            copy(r, k % 8);
            if ((r == 3) or (r == 5))
            {
                t = -1 * t;
            }
            copy(temp, n % 2);
        };
        copy(temp, n + DecToBigint_2(0));
        copy(n, k + DecToBigint_2(0));
        copy(k, temp + DecToBigint_2(0));
        //swap(n, k);
        copy(r, n % 4);
        copy(temp, k % 4);
        //if ((n % 4 == 3) && (k % 4 == 3)) t = -1 * t;
        if ((r == 3) && (temp == 3)) t = -1 * t;
        //n = n % k;
        copy(n, n % k);
        //cout << "\nLoop N: " << BigintToDecimal(n) << " K: " << BigintToDecimal(k);
    };
    freedata(temp);
    freedata(r);
    //cout << "\nN: " << BigintToDecimal(n) << " K: " << BigintToDecimal(k);
    if (k == 1) return t;
    else return 0;
};

bigint lucas_mod(char mode, bigint &n, bigint &p, bigint &q, bigint x)
{
    cout << "\nLucas p: " << BigintToDecimal(p) << "\nq: " << BigintToDecimal(q) << "\nn: " << BigintToDecimal(n);
    bigint n1;
    bigint n2;
    bigint n3;
    if (mode == 'u')
    {
        cout << "\nLucas mode U";
        DecimalToBigint(n1, 0);
        DecimalToBigint(n2, 1);
        DecimalToBigint(n3, BigintToDecimal (p));
        //cout << "\nInitialize Lucas sequence n3: " << BigintToDecimal(n3);
    }
    else if (mode == 'v')
    {
        cout << "\nLucas mode V";
        DecimalToBigint(n1, 2);
        DecimalToBigint(n2, BigintToDecimal(p));
        copy(n3, p * DecToBigint_2 (1));
        copy(n3, n3 * p);
        copy(n3, n3 - q);
        copy(n3, n3 - q);
        //cout << "\nInitialize Lucas sequence n3: " << BigintToDecimal(n3);
    }
    else
    {
        cout << "Lucas WTF ? U hay V?\n";
        return DecToBigint_2 (-1);
    };
    bigint m;
    DecimalToBigint (m, 2);
    bigint gay;
    bigint one;
    DecimalToBigint(one, 1);
    bigint zero; DecimalToBigint(zero, 0);
    if (n == 0) return n1; else if (n == 1) return n2; else if (n == 2) return n3;
    cout << "\np: " << BigintToDecimal(p) << "\nq: " << BigintToDecimal(q);
    cout << "\nLucas sequence n1: " << BigintToDecimal(n1);
    cout << "\nLucas sequence n2: " << BigintToDecimal(n2);
    cout << "\nLucas sequence n3: " << BigintToDecimal(n3);
    while (m > n == -1)
    {
        cout << "\nm: " << BigintToDecimal(m) << "n: " << BigintToDecimal(n);
        cout << "\n Lucas N3: " << BigintToDecimal(n3);
        if (n3 > zero == 0) { cout << "\nLUCAS FOUND ZERO AT " << BigintToDecimal(m) << "\n"; };
        copy(n1, n2 * one);
        copy(n2, n3 * one);
        copy(gay, n1 * q);
        //copy(gay, gay % x);
        //cout << "\nQ * (N-2): " << BigintToDecimal(gay);
        copy(n3, n2 * p);
        //copy(n3, n3 % x);
        //cout << "\nP * (N-1):  " << BigintToDecimal(n3);
        copy(n3, n3 - gay);
        //cout << "\n Lucas N3: " << BigintToDecimal(n3);
        copy(n3, n3 % x);
        copy(m, m + one);
        //if (m > DecToBigint_2(35000) == 0) { cout << "\n PAUSE FOR DEBUGGING \n"; while (true) {}; };
    };
    cout << "\n Lucas N1: " << BigintToDecimal(n1);
    cout << "\n Lucas N2: " << BigintToDecimal(n2);
    cout << "\n Lucas N3: " << BigintToDecimal(n3);
    cout << "\nLucas done\n";
    return n3;
};

bool Lucas_test(bigint &x, bigint &D, bigint &p, bigint &q)
{
    cout << "\nLucas OG X: " << BigintToDecimal(x);
    Bigint d;
    copy(d, x + DecToBigint_2(1));
    cout << "\nLucas OG D: " << BigintToDecimal(d);
    cout << "\n";
    //D = 2^x * d;
    int s = 0;
    Bigint zero = DecToBigint_2(0);
    Bigint pwm_result;
    Bigint temp_d;

    copy(zero, d % 2);
    cout << "\nD % 2: " << BigintToDecimal(zero);
    cout << "\nOG D: " << BigintToDecimal(d);
    copy(d, d / DecToBigint_2(2));
    cout << "\nD/2: " << BigintToDecimal(d);
    while (zero > DecToBigint_2(0) == 0)
    {
        //D = 2^(x-1) * d
        cout << "\nD: " << BigintToDecimal(d);
        cout << "\nX: " << BigintToDecimal(x);
        DecimalToBigint(temp_d, BigintToDecimal(d));
        copy(pwm_result, lucas_mod('v', d, p, q, x));
        cout << "\nLucas: " << BigintToDecimal(pwm_result);
        copy(pwm_result, pwm_result % x);
        cout << "\nLucas % X: " << BigintToDecimal(pwm_result);
        
        if ((pwm_result > DecToBigint_2(0)) == 0) return 1;

        copy(zero, d % 2);
        if (zero > DecToBigint_2(0) != 0) break;
        copy(d, d / DecToBigint_2(2));
        cout << "\nD divided: " << BigintToDecimal(d);
    } ;
    //D = 2^0 * d
    copy(pwm_result, lucas_mod('u', d, p, q, x));
    cout << "\nLucas: " << BigintToDecimal(pwm_result);
    copy(pwm_result, pwm_result % x);
    cout << "\nLucas % X: " << BigintToDecimal(pwm_result);
    if ((pwm_result > DecToBigint_2(0)) == 0) return 1;
    return 0;
};
bool PrimeCheck(const bigint x)
{
    bigint zero;
    bigint modResult;
    DecimalToBigint(zero, 0);
    
    //Early detection, i = 2 ---> 10000 to check for early prime
    for (int i = 2; i < 10000; i++)
    {
        copy(modResult, x % i);
        if (modResult == zero)
        {
            bigint temp;
            DecimalToBigint(temp, i);
            if (x == temp) { break; };
            printf("\nKHONG PHAI PRIME, chia het cho %d", i);
            return 0;
        };
    };
    //Miller Rabin
    cout << "\nBEGIN MILLER RABIN\nx: " << BigintToDecimal(x);
    if (PrimeTest(x) != 1) return 0;
    printf("\nMiller Rabin done\n");
    //Jacobi symbol calculation
    copy(modResult, DecToBigint_2(5));
    int Jacobi;
    int sign = 1;
    Bigint k;
    Bigint n;
    Jacobi = 1;
    while (true)
    {
        //cout << "\n1 / modResult: " << BigintToDecimal(modResult) << " x " << BigintToDecimal(x) << " n " << BigintToDecimal(n);
        copy(k, modResult * DecToBigint_2(1));
        //copy(n, x * DecToBigint_2(1));
        DecimalToBigint(n, BigintToDecimal(x));
        //cout << "\n2 / modResult: " << BigintToDecimal(modResult) << " x " << BigintToDecimal(x) << " n " << BigintToDecimal(n);
        //cout << "\n";
        // N VOI K BI SWAP BEN TRONG FUNCTION JACOBI
        Jacobi = jacobi_cpp(n, k);
        //freedata(n);
        //cout << "\nJACOBII: " << BigintToDecimal(modResult) << " " << Jacobi << " n " << BigintToDecimal(n);
        if (Jacobi == -1) { cout << "\nJACOBI: "  << Jacobi << "   (k/x) = " << BigintToDecimal(modResult) << " / " << BigintToDecimal(x); break; };
        if (Jacobi == 2) return 0;
        copy(modResult, modResult + DecToBigint_2(2 * sign));
        copy(modResult, modResult * DecToBigint_2(-1));
        sign = sign * -1;
    };
    cout << "\n Jacobi DONE \n";
    //modResult la D Set P = 1 and Q = (1 - D)/4
    //Perform a strong Lucas probable prime test on n using parameters D, P, and Q.
    bigint P;
    bigint Q;
    DecimalToBigint(P, 1);
    copy(Q, DecToBigint_2(1) - modResult);
    copy(Q, Q / DecToBigint_2(4));
    DecimalToBigint(Q, BigintToDecimal (Q));
    copy(n, x + DecToBigint_2(0));
    cout << "\nLucas OG X: " << BigintToDecimal(x);
    cout << "\nLucas OG N: " << BigintToDecimal(n);
    if (Lucas_test(n, modResult, P, Q) == 1)
    {
        freedata(zero);
        freedata(modResult);
        printf("\nSo nguyen to (probably)\n");
        return 1;
    };
    freedata(zero);
    freedata(modResult);
    return 0;
};
