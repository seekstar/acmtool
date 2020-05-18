bitset<MAXN> is_prime;
vector<int> prime;
void get_sigma(int sigma[], int n) {
	static int pk[MAXN];
	is_prime.set();
	sigma[1] = 1;
	for (int i = 2; i <= n; ++i) {
		if (is_prime[i]) {
			prime.push_back(i);
			pk[i] = i;
			sigma[i] = i + 1;
		}
		for (int pr : prime) {
			int now = i * pr;
			if (now > n) break;
			is_prime[now] = false;
			if (i % pr == 0) {  //pr is the minimum prime factor of i
				pk[now] = pk[i] * pr;
				sigma[now] = sigma[i] + sigma[i / pk[i]] * pk[now];
				break;
			} else {
				pk[now] = pr;
				sigma[now] = (1 + pk[now]) * sigma[i];
			}
		}
	}
}
