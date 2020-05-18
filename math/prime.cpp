//O(sqrt(num))
template<typename T>
bool IsPrime(T num) {
    T i;
    if(num == 2)
        return 1;
    else if(num < 2 || num % 2 == 0)
        return 0;
    for(i = 3; i * i <= num; i+=2)
        if(num % i == 0)
            break;
    return i * i > num;
}

//O(sqrt(n))
template<typename T>
void PrimeFactor(T n, vector<T>& factor) {
    factor.clear();
    for (T i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            factor.push_back(i);
            do {
                n /= i;
            } while (n % i == 0);
        }
    }
    if (n != 1)
        factor.push_back(n);
}

template<typename T>
T LeastPrimeFactor(T n)
{
	if(0 == n % 2)return 2;
	T i;
	for(i = 3; i*i <= n && n % i != 0; i += 2);
	return i*i <= n ? i : n;
}

template<typename T>
pair<int, int> FactorSum(T x, int p)
{
    LL sum = 1;
    int FactorNum = 1;
    int cnt;
    LL tmp;
    LL tmp_sum;
    for(int i = 0; (LL)prime[i] * prime[i] <= x; ++i)
    {
        if(0 == x % prime[i])
        {
            x /= prime[i];
            cnt = 1;
            tmp_sum = 1 + prime[i];
            tmp = prime[i];
            while(x % prime[i] == 0)
            {
                x /= prime[i];
                (tmp *= prime[i]) %= p;
                (tmp_sum += tmp) %= p;
                ++cnt;
            }
            FactorNum *= (1 + cnt);
            (sum *= tmp_sum) %= p;
        }
    }
    if(x > 1)
    {
        (sum *= (1 + x)) %= p;
        FactorNum *= 2;
    }
    return make_pair((int)sum, FactorNum);
}

template<typename T>
void PrintFactor(T x) {
	if(0 == x) return;
	for(LL i = 2; i * i <= x; ++i) {
		int cnt = 0;
		while(0 == x % i) {
			x /= i;
			++cnt;
		}
		if(cnt) {
			printf("%lld", i);
			if(cnt > 1) {
				printf("^%d", cnt);
			}
			if(x > 1)
				printf(" * ");
		}
	}
	if(x > 1)printf("%lld", x);
	putchar('\n');
}

