//O(logn)
//n > 2 && n is odd && n != a
bool Test(LL n, LL a) {
	LL u = n - 1;
	while (!(u & 1)) u >>= 1;
	LL x = mpow(a, u, n);
	while (u < n) {
		auto pre = x;
		u <<= 1;
		x = (__int128)x * x % n;
		if (x == 1 && pre != 1 && pre != n - 1)
			return false;
	}
	if (x != 1) return false;
	return true;
}
//n <= 1e16
bool IsPrime(LL n) {
	const static int a[] = {2, 3, 7, 61, 24251};
	if (n < 2) return false;
	if (2 == n) return true;
	if (!(n & 1)) return false;
	if (n == 46856248255981LL) return false;
	for (int i = 0; i < 5; ++i) {
		if (a[i] == n) return true;
		if (!Test(n, a[i])) return false;
	}
	return true;
}

//rand
bool IsPrime(LL n) {
	if (n < 2) return false;
	if (2 == n) return true;
	if (!(n & 1)) return false;
	for (int i = 0; i < 10; ++i) {
		if (!Test(n, rand64() % (n-1) + 1)) return false;
	}
	return true;
}

