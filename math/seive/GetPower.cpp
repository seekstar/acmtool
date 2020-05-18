bitset<MAXK> is_prime;
vector<int> prime;
//f[1..n]
//f[x] = sum_{i=1}^x i^k
void GetPower(int f[], int k, int n) {
    is_prime.set();
    f[0] = 0, f[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (is_prime[i]) {
            prime.push_back(i);
            f[i] = mpow(i, k, p);
        }
        for (int pr : prime) {
            int now = i * pr;
            if (now > n) break;
            is_prime[now] = false;
            f[now] = (LL)f[pr] * f[i] % p;
            if (i % pr == 0) {  //pr is the minimum prime factor of i
                break;
            }
        }
    }
}