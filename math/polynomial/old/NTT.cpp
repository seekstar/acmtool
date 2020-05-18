//g = 3
//998244353, img = 86583718
//1004535809 = 479*2^21+1, img = 483363861
//469762049, img = 19610091
//tp == false means NTT^-1
void NTT(int a[], int n, bool tp) {
	for (int i = 0, j = 0; i < n; ++i) {
		if (i > j) swap(a[i], a[j]);
		for (int k = n >> 1; (j ^= k) < k; k >>= 1);
	}
	for (int i = 2; i <= n; i <<= 1) {
		int wn = mpow(3, tp ? (p - 1) / i : p - 1 - (p-1)/i, p);
		for (int pa = i >> 1, j = 0; j < n; j += i) {
			for (int w = 1, k = 0; k < pa; ++k, w = (LL)w * wn % p) {
				int t = (LL)w * a[j + k + pa] % p;
				a[j + k + pa] = Sub(a[j + k] - t, p);
				AddMod(a[j + k] += t, p);
			}
		}
	}
	if (!tp)
		for (int i = 0, n1 = mpow(n, p-2, p); i < n; ++i)
			a[i] = (LL)a[i] * n1 % p;
}

int FindPowOf2(int to) {
	int n;
	for (n = 1; n < to; n <<= 1);
	return n;
}
void Fill(int a[], int na, int n) {
	for (; na < n; ++na)
		a[na] = 0;
}
//a and b are destroyed
//Allow c == a or b
void Mul(int c[], int a[], int na, int b[], int nb) {
	int n = FindPowOf2(na + nb);	//in FFT
	Fill(a, na, n);
	Fill(b, nb, n);
	NTT(a, n, true);
	NTT(b, n, true);
	for (int i = 0; i < n; ++i)
		c[i] = (LL)a[i] * b[i] % p;
	NTT(c, n, false);
}

//n == 2^k
//mod x^n
//b != a
//Do not need Initialize b
//The upper n elements of b is 0
void Inv(int b[], const int a[], int n) {
    static int t[MAX2N];
    if (n == 1) {
        b[0] = mpow(a[0], p - 2, p);
        b[1] = 0;	//necessary?
        return;
    }
    Inv(b, a, n >> 1);
    memset(b + n, 0, n * sizeof(b[0]));
    NTT(b, n << 1, true);
    memcpy(t, a, n * sizeof(int));
    memset(t + n, 0, n * sizeof(int));
    NTT(t, n << 1, true);
    for (int i = 0, r = n << 1; i < r; ++i)
        b[i] = (LL)b[i] * Sub(2 - (LL)t[i] * b[i] % p, p) % p;
    NTT(b, n << 1, false);
    memset(b+n, 0, n * sizeof(int));
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
//quo[i] != 0 if i >= nq
//len(rem) == nb - 1
void DivMod(int quo[], int& nq, int rem[], const int a[], int na, int b[], int nb) {
	static int t[MAX2N];
	memcpy(t, a, na * sizeof(a[0]));
	Div(quo, nq, t, na, b, nb);
	reverse(b, b + nb);	//reverse back
	memcpy(t, quo, nq * sizeof(t[0]));
	Mul(rem, t, nq, b, nb);
	for (int i = 0; i < nb - 1; ++i)
		rem[i] = Sub(a[i] - rem[i], p);
}

//Allow b == a
void Derivation(int b[], int a[], int n) {
	for (int i = 1; i < n; ++i)
		b[i-1] = (LL)i * a[i] % p;
	b[n-1] = 0;
}
//Allow b == a
//mod x ^ n
void Integral(int b[], int a[], int n) {
	for (int i = n - 1; i; --i)
		b[i] = (LL)a[i-1] * Inv(i, p) % p;
	b[0] = 0;
}

//b = ln(a) mod x ^ n
//n == 2 ^ k
//Allow b == a
void ln(int b[], int a[], int n) {
	static int t[MAX2N];
	Inv(t, a, n);
	Derivation(a, a, n);
	Mul(a, a, n, t, n);
	Integral(b, a, n);
}

//O(nlog n)
//If a[0] == 0, then b0 == 1
//n == 2^k
//b != a
//The upper n elements of b is 0
void exp(int b[], int b0, const int a[], int n) {
    static int t[MAX2N];
    if (1 == n) {
        b[0] = b0;
        b[1] = 0;
    } else {
        exp(b, b0, a, n >> 1);
        memcpy(t, b, n * sizeof(b[0]));
        ln(t, t, n);
        t[0] = Sub(Add(1 + a[0], p) - t[0], p);
        for (int i = 1; i < n; ++i)
            t[i] = Sub(a[i] - t[i], p);
        Mul(b, b, n, t, n);
        memset(b + n, 0, n * sizeof(b[0]));
    }
}

//pg is the primitive root of p
int KthRoot(int x, int k, int p, int pg) {
    int ret = mpow(pg, BSGS(pg, x, p) / k, p);
    return min(ret, p - ret);
}

//Exists b0 such that b0^k = a0 (mod p)
//n == 2^kk
//b != a
void KthRoot(int b[], int a[], int n, int k) {
    int b0 = KthRoot(a[0], k, p, 3);
    ln(a, a, n);
    int tmp = Inv(k, p);
    for (int i = 0; i < n; ++i)
        a[i] = (LL)a[i] * tmp % p;
    exp(b, b0, a, n);
}

//a[0] != 0
//O(nlgn)
//n == 2^kk
//b != a
void pow(int b[], int a[], int n, int k) {
    int b0 = mpow(a[0], k, p);
    ln(a, a, n);
    for (int i = 0; i < n; ++i)
        a[i] = (LL)a[i] * k % p;
    exp(b, b0, a, n);
}
//Allow a[0] == 0
//Allow n != 2^kk
//mod x^na
void pow(int a[], int na, int k) {
    static int t[MAX2N];
    int l0;
    for (l0 = 0; l0 < na && 0 == a[l0]; ++l0);
    memmove(a, a + l0, (na - l0) * sizeof(a[0]));
    int n = FindPowOf2(na - l0); //if na == 0, then n == 1
    Fill(a, na - l0, n);
    pow(t, a, n, k);
    Fill(t, n, na);
    l0 = min((LL)l0 * k, (LL)na);
    memset(a, 0, l0 * sizeof(a[0]));
    memcpy(a + l0, t, (na - l0) * sizeof(a[0]));
}


