struct POW_MOD {
    const static int STEP = 31624;
    int f[STEP], g[STEP], p, s; //s: step
    template <typename T>
    void Init(int y, T maxq, int _p) {
        p = _p;
        s = sqrt(maxq) + 1;
        f[0] = g[0] = 1;
        for (int i = 1; i < s; ++i)
            g[i] = (LL)g[i-1] * y % p;
        y = (LL)g[s-1] * y % p;
        for (int i = 1, now = s; now <= p; ++i, now += s)
            f[i] = (LL)f[i-1] * y % p;
    }
    int pow(int z) {
        return (LL)f[z / s] * g[z % s] % p;
    }
};
