vector<int> prime;
bitset<MAXN>is_prime;
void PrimeTable() {
    is_prime.set();
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i < MAXN; ++i) {
        if (is_prime[i])
            prime.push_back(i);
        for (int pr : prime) {
            int now = pr * i;
            if (now >= MAXN) break;
            is_prime[now] = false;
            if (i % pr == 0) break;
        }
    }
}
