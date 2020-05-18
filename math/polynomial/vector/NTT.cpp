typedef vector<int> vi;

void Fill(vi& a, int to) {
    if (a.size() < to)
        a.resize(to, 0);
}

//tp == false means NTT^-1
void NTT(vi& a, bool tp) {
    int n = a.size();
    int sft = __builtin_ctz(size) - __builtin_ctz(n);
    for (int i = 0; i < n; ++i)
        if (i < (bitrev[i] >> sft))
            swap(a[i], a[bitrev[i] >> sft]);
    for (int i = 2; i <= n; i <<= 1) {
        for (int pa = i >> 1, j = 0; j < n; j += i) {
            for (int k = 0; k < pa; ++k) {
                int t = (LL)w[tp][pa + k] * a[j + k + pa] % p;
                a[j + k + pa] = Sub(a[j + k] - t, p);
                AddMod(a[j + k] += t, p);
            }
        }
    }
    if (!tp)
        for (int i = 0; i < n; ++i)
            a[i] = (LL)a[i] * invs[n] % p;
}

//a != b
//Allow c == a or b
//c.size() = a.size() + b.size() - 1
void Mul(vi& c, vi& a, vi& b) {
    int len = a.size() + b.size() - 1;
    int n = FindPowOf2(len);	//in FFT
    a.resize(n, 0);
    b.resize(n, 0);
    NTT(a, true);
    NTT(b, true);
    c.resize(n);
    for (int i = 0; i < n; ++i)
        c[i] = (LL)a[i] * b[i] % p;
    NTT(c, false);
    c.resize(len);
}

//n == 2^k
//mod x^n
//b != a
//Do not need Initialize b
void Inv(vi& b, const vi& a, int n) {
    static vi t(MAX2N);
    if (n == 1) {
        b.resize(1);
        b[0] = mpow(a[0], p - 2, p);
        return;
    }
    Inv(b, a, n >> 1);
    b.resize(n << 1, 0);
    NTT(b, true);
    t.assign(a.begin(), a.begin() + n);
    t.resize(n << 1, 0);
    NTT(t, true);
    for (int i = 0, r = n << 1; i < r; ++i)
        b[i] = (LL)b[i] * Sub(2 - (LL)t[i] * b[i] % p, p) % p;
    NTT(b, false);
    b.resize(n);
}
void Inv(vi& b, vi& a) {
    int n = a.size();
    a.resize(FindPowOf2(n), 0);
    Inv(b, a, a.size());
    b.resize(n);
}

