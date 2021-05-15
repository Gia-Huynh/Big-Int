#include"IO.h"

void Infor(int* &a, int& n)
{
	string t;
	ifstream fi("Input.txt");
	while (!fi.eof())
	{
		getline(fi, t);
		n++;
	}
	a = new int[n];
	int cnt = 0;
	fi.seekg(0, fi.beg);
	while (!fi.eof())
	{
		getline(fi, t);
		int k = countspace(t);
		a[cnt] = k;
		cnt++;
	}
	fi.close();
}

void IO()
{
	string t;
	int* a = nullptr;
	int n = 0;
	Infor(a, n);
	ifstream fi("Input.txt");
	ofstream fo("Output.txt");
	for (int i = 0; i < n; i++)
	{
		if (a[i] == 2)
		{
			string t1, t2, t3;
			fi >> t1;
			fi >> t2;
			fi >> t3;
			getline(fi, t);
			if (t1 == "2")
			{
				if (t2 == "10")
				{
					bigint z;
					BinaryToBigint(z, t3);
					fo << BigintToDecimal(z);
					freedata(z);
				}
			}
			else
			{
				if (t2 == "2")
				{
					bigint z;
					DecimalToBigint(z, t3);
					fo << BigintToBinary(z);
					freedata(z);
				}
				else
				{
					bigint z;
					DecimalToBigint(z, t3);
					copy(z, ~z);
					fo << BigintToDecimal(z);
					freedata(z);
				}
			}
		}
		else
		{
			string t1, t2, t3, t4;
			fi >> t1;
			fi >> t2;
			fi >> t3;
			fi >> t4;
			getline(fi, t);
			if (t1 == "2")
			{
				if (t3 == "+")
				{
					fo << AddBinary(t2, t4);
				}
				else if (t3 == "*")
				{
					fo << BinaryMultiplication(t2, t4);
				}
				else if (t3 == "-")
				{
					fo << BinarySubstraction(t2, t4);
				}
				else
					fo << BinaryDivision(t2, t4);
			}
			else
			{
				if (t3 == "+")
				{
					bigint x, y, z;
					DecimalToBigint(x, t2);
					DecimalToBigint(y, t2);
					copy(z, x + y);
					fo << BigintToDecimal(z);
					freedata(x);
					freedata(y);
					freedata(z);
				}
				else if (t3 == "-")
				{
					bigint x, y, z;
					DecimalToBigint(x, t2);
					DecimalToBigint(y, t2);
					copy(z, x - y);
					fo << BigintToDecimal(z);
					freedata(x);
					freedata(y);
					freedata(z);
				}
				else if (t3 == "*")
				{
					bigint x, y, z;
					DecimalToBigint(x, t2);
					DecimalToBigint(y, t2);
					copy(z, x * y);
					fo << BigintToDecimal(z);
					freedata(x);
					freedata(y);
					freedata(z);
				}
				else if(t3 == "/")
				{
					bigint x, y, z;
					DecimalToBigint(x, t2);
					DecimalToBigint(y, t2);
					copy(z, x / y);
					fo << BigintToDecimal(z);
					freedata(x);
					freedata(y);
					freedata(z);
				}

			}
		}
		if (i < n-1)
			fo << endl;
	}
	fi.close();
	fo.close();
}