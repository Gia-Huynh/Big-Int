/*function jacobi_lua(n, k)
  assert(k > 0 and k % 2 == 1)
  n = n % k
  t = 1
  while n ~= 0 do
    while n % 2 == 0 do
      n = n / 2
      r = k % 8
      if r == 3 or r == 5 then
        t = -t
      end
    end
    n, k = k, n
    if n % 4 == 3 and k % 4 == 3 then
      t = -t
    end
    n = n % k
  end
  if k == 1 then
    return t
  else
    return 0
  end
end*/

int jacobi_cpp (Bigint n, Bigint k)
{
	if ((k<=0) || (k%2 != 1)) 
	{printf ("ERROR IN JACOBI CALCULATION, ASSERTION K FAILED"); return 2;};
	n = n % k;
	int t = 1;
	while (n != 0)
	{
		while (n%2 == 0)
		{
			n = n/2;
			r = k%8;
			if ((r==3) or (r==5))
			{ t = -1 * t;}
		};
		swap (n,k);
		if ((n%4 == 3) &&  (k%4 == 3)) t = -1 * t;
		n = n % k;
	};
	if (k==1) return t; else return 0;
};