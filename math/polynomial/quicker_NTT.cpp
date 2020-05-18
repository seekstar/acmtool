//tp == false means NTT^-1
void NTT(int a[], int n, bool tp) {
    static ULL t[MAX2N];
    int sft = __builtin_ctz(size) - __builtin_ctz(n);
    for (int i = 0, j = 0; i < n; ++i)
        t[bitrev[i] >> sft] = a[i];
    for (int i = 2; i <= n; i <<= 1) {
        for (int pa = i >> 1, j = 0; j < n; j += i) {
            for (int k = 0; k < pa; ++k) {
                auto tmp = t[j + k + pa] * w[tp][pa + k] % p;
                t[j + k + pa] = t[j + k] + p - tmp;
                t[j + k] += tmp;
            }
        }
    }
    for (int i = 0; i < n; ++i)
        a[i] = t[i] % p;
    if (!tp)
        for (int i = 0; i < n; ++i)
            a[i] = (LL)a[i] * invs[n] % p;
}
