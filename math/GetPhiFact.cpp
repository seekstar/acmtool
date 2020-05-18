void GetPhiFact(int f[], int n, int p) {
    PrimeTable();
    for (int i = 1, now = 1; i <= n; ++i) {
        if (is_prime[i])
            now = (LL)now * Inv(i, p) % p * (i - 1) % p;
        now = (LL)now * i % p;
        f[i] = now;
    }
}
