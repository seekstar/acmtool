template <typename T>
struct dj_sieve {
    const static int maxn = 2;
    int N, ns[maxn];   //Sum(ns[i] / x)
    T s[MAXN23], rec[maxn][MAXN12];

    void Init(int num, int mn, void(*get_sum)(T*, int)) {
        N = pow(mn, 2.0 / 3);
        get_sum(s, N);
        for (int i = 0; i < num; ++i)
            memset(rec[i], -1, (sqrt(ns[i]) + 5) * sizeof(T));
    }

    virtual T hs(int) = 0;
    virtual T gs(int) = 0;

    //h = f * g
    T GetSum(int sel, int x) {
        if (x <= N) return s[x];
        int pos = ns[sel] / x;
        T& ans = rec[sel][pos];
        if (~ans)
            return ans;
        ans = hs(x);
        for (int l = 2, r; l <= x; l = r + 1) {
            r = (x / (x / l));
            ans = (ans - (LL)(gs(r) - gs(l - 1)) * GetSum(sel, x / l)) % p;
        }
        //ans /= gs(1);	//if gs(1) != 1
        SubMod(ans, p);
        return ans;
    }
};

/*
int ans = 0;
    for (int t = 1, last = 0, r; t <= bound; t = r + 1) {
        int r1 = n / (n / t), r2 = m / (m / t), sel;
        if (r1 < r2) {
            r = r1;
            sel = 0;
        } else {
            r = r2;
            sel = 1;
        }
        int now = hs.GetSum(sel, r);
        ans = (ans + (LL)(now - last) * f(n / t) % p * f(m / t)) % p;
        last = now;
    }
*/
