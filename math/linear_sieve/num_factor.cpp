//number of factor
bitset<MAXN> is_prime;
vector<int> prime;
void get_num_factor(int f[], int n) {
    static int pk[MAXN];
    is_prime.set();
    prime.clear();
    f[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (is_prime[i]) {
            prime.push_back(i);
            pk[i] = i;
            f[i] = 2;
        }
        for (int pr : prime) {
            int now = i * pr;
            if (now > n) break;
            is_prime[now] = false;
            if (i % pr == 0) {  //pr is the minimum prime factor of i
                pk[now] = pk[i] * pr;
                f[now] = f[i] + f[i / pk[i]];
                break;
            } else {
                pk[now] = pr;
                f[now] = f[i] << 1;
            }
        }
    }
}
