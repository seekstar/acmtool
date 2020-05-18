template <typename T>
struct dj_sieve {
    unordered_map<LL, T> rec;
    int N;
    T* s;

    void Init(int n23, T* sum) {
        //rec.reserve(pow(n23, 3.0 / 4));	//sqrt(n)
        rec.reserve(n23);
        N = n23;
        s = sum;
    }

    virtual T hs(LL) = 0;
    virtual T gs(LL) = 0;

    //h = f * g
    T GetSum(LL n) {
        if (n <= N) return s[n];
        auto it = rec.find(n);
        if (it != rec.end())
            return it->second;
        T ans = hs(n);
        for (LL l = 2, r; l <= n; l = r + 1) {
            r = (n / (n / l));
            ans = (ans - (LL)(gs(r) - gs(l - 1)) * GetSum(n / l)) % p;
        }
        //ans /= gs(1);	//if gs(1) != 1
        rec.emplace(n, ans);
        return ans;
    }
};