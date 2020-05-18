//euler function
//O(sqrt(n))
//phi(1) = 1
template<typename T>
T phi(T n) {
    T ans = n;
    for(T i = 2; i * i <= n; ++i) {
        if(0 == n % i) {
            (ans /= i) *= (i - 1);
            do {
                n /= i;
            } while (0 == n % i);
        }
    }
    if(n > 1) (ans /= n) *= (n - 1);
    return ans;
}

template <typename T>
T phi(T n) {
    T ans = n;
    for (int pr : prime) {
        if (pr * pr > n) break;
        if (n % pr == 0) {
            (ans /= pr) *= (pr - 1);
            do {
                n /= pr;
            } while (0 == n % pr);
        }
    }
    if (n > 1) (ans /= n) *= (n-1);
    return ans;
}

//O(n)
bitset<MAXN23> is_prime;
vector<int> prime;
template<typename T>
void get_phi(T phis[], int n) {
	is_prime.set();
	phis[1] = 1;
	for(int i = 2; i <= n; ++i) {
		if(is_prime[i]) {
			prime.push_back(i);
			phis[i] = i - 1;
		}
		for (int pr : prime) {
			int now = i * pr;
			if (now > n) break;
			is_prime[now] = false;
			if (i % pr == 0) {  //pr is the minimum prime factor of i
				phis[now] = phis[i] * pr;
				break;
			} else {
				phis[now] = phis[i] * (pr - 1);
			}
		}
	}
}

//O(???)
template<typename T>
void get_phi(T phis[], int n) {
	for(int i = 0; i <= n; ++i)
		phis[i] = i;
	for(int i = 2; i <= n; ++i) {
		if(phis[i] != i)continue;
		--phis[i];
		for(int j = 2*i; j <= n; j += i)
			phis[j] = phis[j] / i * (i-1);
	}
}
