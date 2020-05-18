bitset<MAXN> is_prime;
vector<int> prime;
void get_mu(int mu[], int n) {
    is_prime.set();
    mu[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (is_prime[i]) {
            prime.push_back(i);
            mu[i] = -1;
        }
        for (int pr : prime) {
            int now = i * pr;
            if (now > n) break;
            is_prime[now] = false;
            if (i % pr == 0) {  //pr is the minimum prime factor of i
                mu[now] = 0;
                break;
            } else {
                mu[now] = -mu[i];
            }
        }
    }
}
