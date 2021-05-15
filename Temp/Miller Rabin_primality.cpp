/* https://stackoverflow.com/questions/8287144/modulus-power-of-big-numbers For modulus*/


Bigint powermod(int base, Bigint exponent, Bigint modulus) {
    if (base < 1 || exponent < 0 || modulus < 1)
        return -1
	
    Bigint result = 1;
    while (exponent > 0) {
       if ((exponent % 2) == 1) {
           result = (result * base) % modulus;
		   exponent--;
       }
       base = (base * base) % modulus;
       exponent = exponent / 2;
    }
    return result;
}


int PrimeTest (Bigint n)
{
	if ((n<3) || (n%2 == 0)) 
	{
		printf ("Assertion False, PrimeTest, N<3 or N chia het cho 2\n");
		return 2;
	};
	Bigint d = n-1;
	int s = 0;
	while (d % 2 == 0)
	{
		d = d / 2;
		if (powermod (2, d, n) - n == -1) return 1;
	};
	if (powermod (2, d, n) == 1) return 1;
	return 0;
};