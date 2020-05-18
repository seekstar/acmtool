int Inv(int x, int p) {
	return mpow(x, p-2, p);
}

//x < p
//p must be prime
template <typename T>
T Inv(T x, int p) {
    return 1 == x ? 1 : (LL)(p - p / x) * Inv(p % x, p) % p;
}

//Get inverse elements of positive integers that are <= bound
template<typename T>
void GetInvs(T invs[], T p, T bound) {
    invs[1] = 1;
    for(int i = 2; i <= bound; ++i)
        invs[i] = (LL)(p - p / i) * invs[p % i] % p;
}

