#include <iostream>
#include <limits>
#include <cstring>
#include <cmath>
#include <bitset>
#include <vector>
#include <climits>

using namespace std;

#define DEBUG 0
#define ONLINE_JUDGE

#define MAXN23 10000011

typedef long long LL;

//100003, 300017, 1000033
template <typename key_t, typename val_t>
struct HashMap {
	const static int p = 1000033;	//greater than the number of insertions
	const static val_t NOT_FOUND = numeric_limits<val_t>::min();
	int hd[p], nxt[p], tot;
	key_t keys[p];
	val_t vals[p];
	void Init() {
		tot = 0;
		memset(hd, -1, sizeof(hd));
	}
	//find first if you do not want to shadow
	void emplace_shadow(key_t key, val_t val) {
		//Shadow the previous one
		int ha = key % p;
		nxt[++tot] = hd[ha];
		hd[ha] = tot;
		keys[tot] = key;
		vals[tot] = val;
	}
	val_t find(key_t key) {
		int ha = key % p;
		for (int e = hd[ha]; ~e; e = nxt[e])
			if (keys[e] == key)
				return vals[e];
		return NOT_FOUND;
	}
};

template <typename T>
struct dj_sieve {
	HashMap<int, T> rec;
	int N;
	T* s;

	void Init(int n23, T* a) {
		rec.Init();
		N = n23;
		s = a;
		for (int i = 1; i <= N; ++i)
			s[i] += s[i-1];
	}

	virtual T hs(int) = 0;
	virtual T gs(int) = 0;

	//h = f * g
	T GetSum(int n) {
		if (n <= N) return s[n];
		T ans = rec.find(n);
		if (ans != rec.NOT_FOUND)
			return ans;
		ans = hs(n);
		for (int l = 2, r; l <= n; l = r + 1) {
			r = (n / (n / l));
			ans -= (gs(r) - gs(l - 1)) * GetSum(n / l);
		}
		//ans /= gs(1);	//if gs(1) != 1
		rec.emplace_shadow(n, ans);
		return ans;
	}
};

struct dj_phi : public dj_sieve<LL> {
	inline virtual LL hs(int n) {
		return (LL)n * (n + 1) >> 1;
	}
	inline virtual LL gs(int n) {
		return n;
	}
};

struct dj_mu : public dj_sieve<int> {
	inline virtual int hs(int n) {
		return 1;
	}
	inline virtual int gs(int n) {
		return n;
	}
};

bitset<MAXN23> is_prime;
vector<int> prime;
template <typename T>
void get_mu_phi(int mu[], T phi[], int n) {
    is_prime.set();
    mu[1] = 1;
	phi[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (is_prime[i]) {
            prime.push_back(i);
            mu[i] = -1;
			phi[i] = i - 1;
        }
        for (int pr : prime) {
            int now = i * pr;
            if (now > n) break;
            is_prime[now] = false;
            if (i % pr == 0) {  //pr is the minimum prime factor of i
                mu[now] = 0;
				phi[now] = phi[i] * pr;
                break;
            } else {
                mu[now] = -mu[i];
				phi[now] = phi[i] * (pr - 1);
            }
        }
    }
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.in", "r", stdin);
	freopen("out.out", "w", stdout);
#endif
	static dj_mu smu;
	static dj_phi sphi;

	static int mu[MAXN23];
	static LL phi[MAXN23];

	int T;

	cin >> T;

	int n23 = pow((double)T * INT_MAX, 2.0 / 3);
	get_mu_phi(mu, phi, n23);
	smu.Init(n23, mu);
	sphi.Init(n23, phi);
	while (T--) {
		int n;
		cin >> n;
		cout << sphi.GetSum(n) << ' ' << smu.GetSum(n) << endl;
	}

	return 0;
}
