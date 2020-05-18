struct cpx {
	double r, i;
	inline cpx& operator += (const cpx& rhs) {
		r += rhs.r;
		i += rhs.i;
		return *this;
	}
	inline cpx operator + (const cpx& b) const {
		return cpx{r + b.r, i + b.i};
	}
	inline cpx& operator -= (const cpx& rhs) {
		r -= rhs.r;
		i -= rhs.i;
		return *this;
	}
	inline cpx operator - (const cpx& b) const {
		return cpx{r - b.r, i - b.i};
	}
	inline cpx operator * (const cpx& b) const {
		return cpx{r * b.r - i * b.i, r * b.i + i * b.r};
	}
	inline cpx& operator *= (const cpx& b) {
		return *this = *this * b;
	}
};
const double PI = acos(-1);
//n must be a power of 2
void FFT(cpx a[], int n, int tp) {
	for (int i = 0, j = 0; i < n; ++i) {
		if (i > j) swap(a[i], a[j]);
		for (int k = n >> 1; (j ^= k) < k; k >>= 1);
	}
	for (int i = 2; i <= n; i <<= 1) {
		double theta = PI * 2 / i;
		cpx wn{cos(theta), tp * sin(theta)};
		for (int j = 0, p = i >> 1; j < n; j += i) {
			cpx w{1, 0};
			for (int k = 0; k < p; ++k, w *= wn) {
				cpx t = w * a[j + k + p];
				a[j + k + p] = a[j + k] - t;
				a[j + k] += t;
			}
		}
	}
	if (-1 == tp)
		for (int i = 0; i < n; ++i)
			a[i].r /= n;
}
#define MAX2N 140011
//to = max(na, nb)
int FindPowOf2(int to) {
	int n;
	for (n = 1; n < to; n <<= 1);
	return n;
}
void Fill(cpx a[], int n, int aa[], int nn) {
	for (int i = 0; i < nn; ++i)
		a[i] = cpx{aa[i], 0};
	for (int i = nn; i < n; ++i)
		a[i] = cpx{0, 0};
}
void Mul(int cc[], int& n, int aa[], int na, int bb[], int nb) {
	static cpx a[MAX2N], b[MAX2N];
	n = FindPowOf2(max(na, nb)) << 1;
	Fill(a, n, aa, na);
	Fill(b, n, bb, nb);
	FFT(a, n, 1);
	FFT(b, n, 1);
	for (int i = 0; i < n; ++i)
		a[i] *= b[i];
	FFT(a, n, -1);
	for (int i = 0; i < n; ++i)
		cc[i] = a[i].r + 0.5;
	for (int i = 0, rem = 0; i < n; ++i) {
		cc[i] += rem;
		rem = cc[i] / 10;
		cc[i] %= 10;
	}
}

void Read(int a[], int n) {
	char ch;
	while (n)
		if (isdigit(ch = getchar()))
			a[--n] = ch - '0';
}

