//Binary Indexed Tree
inline int lowbit(int n) {
    return n & -n;
}
template<typename T>
struct BIT {
    const static int maxn = ;
    T s[maxn];	//s[0] is invalid
    int n;

    void Init(int _n) {
        n = _n;
        memset(s, 0, (n+1) * sizeof(s[0]));
    }
    void Init(int _n, int a[]) {
        static T sum[maxn];
        n = _n;
        for (int i = 1; i <= n; ++i) {
            sum[i] = sum[i-1] + a[i];
            s[i] = sum[i] - sum[i - lowbit(i)];
        }
    }
	//x > 0
    void Add(int x, T v) {
        for (; x <= n; x += lowbit(x))
            s[x] += v;
    }
    //The sum of [1, x]
    T Sum(int x) {
        T ans = 0;
        for (; x; x ^= lowbit(x))
            ans += s[x];
        return ans;
    }
};

