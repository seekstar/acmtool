//a * x == b (mod m)
vector<int> ModularEquation(int a, int b, int m) {
    vector<int> ans;
    int d = GCD(a, m);
    if (b % d == 0) {
        int mm = m / d;
        a = (LL)Inv(a / d, mm) * (b / d) % mm;
        for (int i = a; i < m; i += mm) {
            ans.push_back(i);
        }
    }
    return ans;
}
//x ^ k == a (mod 2^n), n >= 1
vector<int> KthResidue_2(int k, int a, int n) {
    if (1 == n) {
        return vector<int>{a & 1};
    } else {
        vector<int> ans;
        auto tmp = KthResidue_2(k, a, n - 1);
        n = 1 << n;
        a %= n;
        for (int v : tmp) {
            if (mpow(v, k, n) == a)
                ans.push_back(v);
            v |= (n >> 1);
            if (mpow(v, k, n) == a)
                ans.push_back(v);
        }
        return ans;
    }
}
//x ^ k == a (mod p^n), gcd(a, p^n) == 1, n >= 1
vector<int> KthResidue_1(int k, int a, int p, int n) {
    if (2 == p) return KthResidue_2(k, a, n);
    int m = mpow(p, n);
    int g = PrimitiveRoot(m);
    a = BSGS(g, a, m);
    p = m / p * (p - 1);
    auto ans = ModularEquation(k, a, p);
    for (int& v : ans) {
        v = mpow(g, v, m);
    }
    return ans;
}
//x ^ k == a (mod p^n)
vector<int> KthResidue(int k, int a, int p, int n) {
    int m = mpow(p, n);

    vector<int> ans;
    int t = 0;
    while (a && a % p == 0) {
        a /= p;
        ++t;
    }
    if (0 == a || t >= n) {
        int base = mpow(p, (n + k - 1) / k);
        for (int i = 0; i < m; i += base) {
            ans.push_back(i);
        }
    } else if (t % k == 0) {
        auto tmp = KthResidue_1(k, a, p, n - t);
        int mul = mpow(p, t / k);
        int base = mul * mpow(p, n - t);
        for (int v : tmp) {
            v *= mul;
            for (int i = v; i < m; i += base) {
                ans.push_back(i);
            }
        }
    }
    return ans;
}
vector<vector<int> > as;
vector<int> ans;
int a[1111], m[1111];
void crt(int i) {
    if (i >= as.size()) {
        ans.push_back(CRT(a, m, as.size()));
    } else {
        for (int v : as[i]) {
            a[i] = v;
            crt(i + 1);
        }
    }
}
//x ^ k == a (mod p^n)
void KthResidue(int k, int a, int mo) {
    static vector<pair<int, int> > factor;
    PrimeFactor(mo, factor);

    for (size_t i = 0; i < factor.size(); ++i) {
        m[i] = mpow(factor[i].first, factor[i].second);
    }

    as.clear();
    for (auto pa : factor) {
        as.emplace_back(KthResidue(k, a, pa.first, pa.second));
    }
    ans.clear();
    crt(0);
}
