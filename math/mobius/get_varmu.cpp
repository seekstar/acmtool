//varmu[n] = sum_{p|n && p is prime}mu(n/p)
bitset<MAXN> is_prime;
vector<int> prime;
template <typename T>
void get_mu_varmu(int mu[], T varmu[], int n) {
	is_prime.set();
	mu[1] = varmu[1] = 1;
	for (int i = 2; i <= n; ++i) {
		if (is_prime[i]) {
			prime.push_back(i);
			varmu[i] = 1;
			mu[i] = -1;
		}
		for (int pr : prime) {
			int now = i * pr;
			if (now > n) break;
			is_prime[now] = false;
			if (i % pr == 0) {  //pr is the minimum prime factor of i
				mu[now] = 0;
				varmu[now] = mu[i];
				break;
			}
			else {
				mu[now] = -mu[i];
				varmu[now] = mu[i] - varmu[i];
			}
		}
	}
}