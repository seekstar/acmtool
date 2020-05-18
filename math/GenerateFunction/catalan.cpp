int catalan[MAXN];
void init_catalan(int len, int p)
{
	GetInvs(invs, p, len);
	catalan[0] = 1;
	for(int i = 1; i < len; ++i)
	{
		catalan[i] = 2LL*(2*i-1) * invs[i+1] % p * catalan[i-1] % p;
	}
}
