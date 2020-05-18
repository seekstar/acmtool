//f[i] = the sum of the square of the factors of i
bitset<MAXC> is_prime;
vector<int> prime;
void get_sum_factor2(int f[], int n, int p) {
    static int pk[MAXC];
    is_prime.set();
    prime.clear();
    f[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (is_prime[i]) {
            prime.push_back(i);
            pk[i] = i;
            f[i] = ((LL)i * i + 1) % p;
        }
        for (int pr : prime) {
            int now = i * pr;
            if (now > n) break;
            is_prime[now] = false;
            if (i % pr == 0) {  //pr is the minimum prime factor of i
                pk[now] = pk[i] * pr;
                f[now] = (f[i] + (LL)f[i / pk[i]] * pk[now] % p * pk[now]) % p;
                break;
            } else {
                pk[now] = pr;
                f[now] = (1 + (LL)pk[now] * pk[now]) % p * f[i] % p;
            }
        }
    }
}
