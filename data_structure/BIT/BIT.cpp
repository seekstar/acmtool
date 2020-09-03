//Binary Indexed Tree
inline int lowbit(int n) {
    return n & -n;
}
template<typename T>
struct BIT {
    const static int maxn = MAXN;
    T s[maxn];	//s[0] is invalid
    int n;

    void Init(int _n) {
        n = _n;
        memset(s, 0, (n+1) * sizeof(s[0]));
    }
    void Init(int _n, const int a[]) {
        n = _n;
		s[0] = a[0];
		for (int i = 1; i <= n; ++i) {
			s[i] = s[i-1] + a[i];
		}
		for (int i = n; i; --i) {
			s[i] -= s[i - lowbit(i)];
        }
    }
	//x > 0
    void add(int x, T v) {
        for (; x <= n; x += lowbit(x))
            s[x] += v;
    }
    //The sum of [1, x]
    T sum(int x) {
        T ans = 0;
        for (; x; x ^= lowbit(x))
            ans += s[x];
        return ans;
    }
};
