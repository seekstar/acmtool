template <typename T>
struct BIT_2DIM {
	const static int maxn1 = 1010, maxn2 = 1010;
	T s[maxn1][maxn2];
	int n1, n2;

	void Init(int _n1, int _n2) {
		n1 = _n1;
		n2 = _n2;
		for (int i = 0; i <= n1; ++i)
			for (int j = 0; j <= n2; ++j)
				s[i][j] = 0;
	}
	void Add(int x1, int x2, T v) {
		for (int t = x2; x1 <= n1; x1 += lowbit(x1))
			for (x2 = t; x2 <= n2; x2 += lowbit(x2))
				s[x1][x2] += v;
	}
	T Sum(int x1, int x2) {
		T ans = 0;
		for (int t = x2; x1; x1 ^= lowbit(x1))
			for (x2 = t; x2; x2 ^= lowbit(x2))
				ans += s[x1][x2];
		return ans;
	}
};
