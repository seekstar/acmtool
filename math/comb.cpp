NumType facts[BOUND], invf[BOUND];  //inverse facts
void InitComb(int n, int p) {
    facts[0] = 1;
    for (int i = 1; i <= n; ++i)
        facts[i] = (LL)facts[i-1] * i % p;
    invf[n] = Inv(facts[n], p);
    for (; n; --n)
        invf[n-1] = (LL)invf[n] * n % p;
}
int comb(int n, int m, int p) {
    return n < 0 || m < 0 || n < m ? 0 : (LL)facts[n] * invf[n-m] % p * invf[m] % p;
}

int lucas(LL n,LL m, int p){
	if (m==0) return 1;
	if (m>n) return 0;
	return C(n%p,m%p)*lucas(n/p,m/p)%p;
}


//Designed for the case that there are only a few queries
//O(m*logm/logp)
template<typename T>
T comb_small(T n, T m, T p)	//O(m)
{
	if(m > n)return 0;
	T i, ans = 1;
	for(i = 1; i <= m; ++i)
		(ans *= i) %= p;
	ans = inv(ans, p);	//inv is O(logp)
	for(i = n - m + 1; i <= n; ++i)
		(ans *= i) %= p;
	return ans;
}
template<typename T>
T comb(T n, T m, T p)
{
	m = min(m, n - m);
	return 0 == m ? 1 : comb_small(n % p, m % p, p) * comb(n / p, m / p, p) % p;
}


//For small data
//comb[i][j] is the methods of selecting j items from i distinct items.
LL comb[MAXN][MAXN];
void GetComb(int n, int p) {
	for (int i = 0; i <= n; ++i) {
		comb[i][0] = comb[i][i] = 1;
		for (int j = 1; j < i; ++j)
			comb[i][j] = (comb[i-1][j-1] + comb[i-1][j]) % p;
	}
}

