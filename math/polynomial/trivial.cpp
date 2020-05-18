//n is high...low
int BigMod(char* n, int p) {
    int ans = 0;
    for (; *n; ++n)
        ans = (10LL * ans + *n - '0') % p;
    return ans;
}
//a[0] != 0
//O(nlgn)
//n == 2^kk
//b != a
void pow_big(int b[], int a[], int n, char k[]) {
    int b0 = mpow(a[0], BigMod(k, p-1), p);
    ln(a, a, n);
    int kp = BigMod(k, p);
    for (int i = 0; i < n; ++i)
        a[i] = (LL)a[i] * kp % p;
    exp(b, b0, a, n);
}

//quo = a / b
//Allow quo == a or b
//b[0...nb-1] is reversed
//quo[i] != 0 if i >= nq
void Div(int quo[], int& nq, int a[], int na, int b[], int nb) {
	static int t[MAX2N];
	nq = na - nb + 1;	//length of quo
	reverse(a, a + na);
	reverse(b, b + nb);
	int len = FindPowOf2(nq);
	Fill(b, nb, len);
	Inv(t, b, len);
	Fill(a, na, len);
	Mul(quo, a, len, t, len);
	reverse(quo, quo + nq);
}
//quo != a && quo != b
//rem != a
//Allow rem == b
//len(rem) == nb - 1
void DivMod(vi& quo, vi& rem, const vi& a, vi& b) {
    static vi t(MAX2N);
    if (a.size() < b.size()) {
        quo.clear();
        rem = a;
    } else {
        t = a;
        Div(quo, t, b);
        reverse(b.begin(), b.end());    //reverse back
        t = quo;
        int nb = b.size();
        Mul(rem, t, b);
        rem.resize(nb - 1);
        for (int i = 0; i < rem.size(); ++i)
            rem[i] = Sub(a[i] - rem[i], p);
    }
}

//a[0] == 0
//n == 2^k
//b != a
//a becomes -i * a
void sin(int b[], int a[], int n) {
    static int t[MAX2N];
    for (int i = 0; i < n; ++i)
        a[i] = (LL)img * a[i] % p;
    exp(b, 1, a, n);
    for (int i = 0; i < n; ++i)
        a[i] = Add(p - a[i], p);
    exp(t, 1, a, n);
    int dem = (LL)invs[2] * mpow(img, p-2, p) % p;
    for (int i = 0; i < n; ++i) {
        SubMod(b[i] -= t[i], p);
        b[i] = (LL)b[i] * dem % p;
    }
}

//a[0] == 0
//n == 2^k
//b != a
//a becomes -i * a
void cos(int b[], int a[], int n) {
    static int t[MAX2N];
    for (int i = 0; i < n; ++i)
        a[i] = (LL)img * a[i] % p;
    exp(b, 1, a, n);
    for (int i = 0; i < n; ++i)
        a[i] = Add(p - a[i], p);
    exp(t, 1, a, n);
    int dem = invs[2];
    for (int i = 0; i < n; ++i) {
        SubMod(b[i] += t[i], p);
        b[i] = (LL)b[i] * dem % p;
    }
}

//n == 2 ^ k
//b != a
//a becomes DFT(a')
void asin(int b[], int a[], int n) {
    static int t[MAX2N];
    memcpy(b, a, n * sizeof(int));
    Square(b, b, n);
    for (int i = 0; i < n; ++i)
        b[i] = Sub(-b[i], p);
    AddMod(++b[0], p);
    KthRoot(t, b, n, 2);
    Inv(b, t, n);
    Derivation(a, a, n);
    Mul(b, a, n, b, n);
    Integral(b, b, n);
}

//n == 2 ^ k
//b != a
//a becomes DFT(a')
void atan(int b[], int a[], int n) {
    static int t[MAX2N];    //t becomes (1+a^2)
    memcpy(t, a, n * sizeof(int));
    Square(t, t, n);
    AddMod(++t[0], p);
    Inv(b, t, n);
    Derivation(a, a, n);
    Mul(b, a, n, b, n);
    Integral(b, b, n);
}

//O(n log^2 n)
const int f0 = 1;
void cdq(int f[], int g[], int l, int r) {
    static int A[MAX2N], B[MAX2N];
    if (l == r) {
        if (0 == l) f[l] = f0;
    } else {
        int mid = (l + r) >> 1;
        cdq(f, g, l, mid);
        int la = mid - l + 1, lb = r - l + 1;
        memcpy(A, f + l, la * sizeof(int));
        memcpy(B, g, lb * sizeof(int));
        Mul(A, A, la, B, lb);
        for (int i = mid + 1; i <= r; ++i)
            AddMod(f[i] += A[i - l], p);
        cdq(f, g, mid + 1, r);
    }
}
void cdq_ntt(int f[], int g[], int n) {
    memset(f, 0, n * sizeof(int));
    cdq(f, g, 0, n-1);
}

struct FastCalc {
    const static int maxm = MAXM;
    vector<int> P[maxm];
    int x[maxm], m;
    void GetP(int rt, int l, int r) {
        P[rt].resize(r - l + 2);
        if (l == r) {
            P[rt][0] = Sub(-x[l], p);
            P[rt][1] = 1;
        } else {
            int mid = (l + r) >> 1;
            GetP(ls(rt), l, mid);
            GetP(rs(rt), mid+1, r);
            Mul_keep(P[rt].data(), P[ls(rt)].data(), mid - l + 2, P[rs(rt)].data(), r - mid + 1);
        }
    }
};
