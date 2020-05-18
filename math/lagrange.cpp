//Given f(0), f(1), f(2), ..., f(k), f is a polynomial of degree k
//calculate f(n)
struct LAGRANGE {
    const static int maxk = MAXK;
    int invs[maxk], invf[maxk], pre[maxk], suf[maxk], a[maxk];
    LAGRANGE() {
        GetInvs(invs, p, maxk - 1);
        invf[0] = invf[1] = 1;
        for (int i = 2; i < maxk; ++i)
            invf[i] = (LL)invf[i-1] * invs[i] % p;
    }
    template <typename T>
    void Init(T n, int k) {
        if (n <= k) return;
        n %= p;
        pre[0] = n, suf[k+1] = 1;
        for (int i = 1; i <= k; ++i)
            pre[i] = (LL)pre[i-1] * (n - i) % p;
        for (int i = k; i >= 0; --i)
            suf[i] = (LL)suf[i + 1] * (n - i) % p;
        for (int i = 0; i <= k; ++i) {
            a[i] = (LL)(i ? pre[i-1] : 1) * suf[i+1] % p * invf[i] % p * invf[k-i] % p;
            if ((k-i) & 1) a[i] = Sub(-a[i], p);
        }
    }
    //f[0..k]
    template <typename T>
    int run(const int f[], int k, T n) {
        if (n <= k) return f[n];
        LL fn = 0;
        for (int i = 0; i <= k; ++i)
            fn += (LL)a[i] * f[i] % p;
        return fn % p;
    }
    template <typename T>
    int solve(const int f[], int k, T n) {
        Init(n, k);
        return run(f, k, n);
    }
};
