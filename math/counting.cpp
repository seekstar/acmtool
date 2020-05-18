//Count the method of dyeing. k colors, n grids, every color must be used.
//O(k*log(n))
LL dyeing(int n, int k, int p)
{
	LL a = mpow(k, n, p);
	for(int i = 1; i < k; ++i)
	{
		(a += (i&1 ? -1 : 1) * c[k][i] * mpow(k-i, n, p) % p) %= p;
	}
	return (a+p)%p;
}
//dp version
void InitDyeing(void)
{
	for(int j = 0; j < 55; ++j)
	{
		dyeing[1][j] = 0;
	}
	dyeing[1][1] = 1;
	for(int i = 2; i < 400; ++i)
	{
		dyeing[i][0] = 0;
		for(int j = 1; j < 55; ++j)
		{
			dyeing[i][j] = (dyeing[i-1][j-1] + dyeing[i-1][j]) % p * j % p;
		}
	}
}
