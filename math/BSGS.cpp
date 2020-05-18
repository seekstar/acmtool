//Here assume that p is prime.
//O(sqrt(p))
//minimum ans s.t. y ^ ans = z (mod p)
//gcd(y, p) == 1
//0 <= z < p
int BSGS(int y, int z, int p) {
	z %= p;
	int rem = sqrt(p) + 1;
	unordered_map<int, int> rec(rem);
	for (int i = 0, yi = 1; i < rem; ++i, yi = (LL)yi * y % p)
		rec.emplace(yi, i);
	y = mpow(Inv(y, p), rem, p);
	for (int i = 0, lim = p / rem + 1; i < lim; ++i, z = (LL)z * y % p) {
		auto it = rec.find(z);
		if (it != rec.end())
			return i * rem + it->second;
	}
	return -1;
}

//O(sqrt(pq))
//minimum ans s.t. y ^ ans = z (mod p)
//gcd(y, p) == 1
//0 <= z < p
int BSGS(int y, int z, int p) {
	z %= p;
	static HashMap<int, int> rec;
	rec.Init();
	int rem = sqrt(p) + 1;
	for (int i = 0, yi = 1; i < rem; ++i, yi = (LL)yi * y % p)
		if (rec.find(yi) == rec.NOT_FOUND)
			rec.emplace_shadow(yi, i);
	y = mpow(Inv(y, p), rem, p);
	for (int i = 0, lim = p / rem + 1; i < lim; ++i, z = (LL)z * y % p) {
		int res = rec.find(z);
		if (res != rec.NOT_FOUND)
			return i * rem + res;
	}
	return -1;
}


//O(sqrt(pq))
//minimum ans s.t. y ^ ans = z (mod p)
//gcd(y, p) == 1
int lim, rem, base;
unordered_map<int, int> rec;
//q is the number of queries
void InitBSGS(int y, int p, int q) {
    rec.clear();
    rem = sqrt((double)p * q) + 1;
	rec.reserve(rem);
    lim = p / rem + 1;
    for (int i = 0, yi = 1; i < rem; ++i, yi = (LL)yi * y % p)
        rec.emplace(yi, i);
    base = mpow(mpow(y, p-2, p), rem, p);
}
int BSGS(int z, int p) {
    for (int i = 0; i < lim; ++i, z = (LL)z * base % p) {
        auto it = rec.find(z);
        if (it != rec.end())
            return i * rem + it->second;
    }
    return -1;
}

//O(sqrt(pq))
//minimum ans s.t. y ^ ans = z (mod p)
//gcd(y, p) == 1
int lim, rem, base;
HashMap<int, int> rec;
//q is the number of queries
void InitBSGS(int y, int p, int q) {
	rec.Init();
	rem = sqrt((double)p * q) + 1;
	lim = p / rem + 1;
	for (int i = 0, yi = 1; i < rem; ++i, yi = (LL)yi * y % p)
		if (rec.find(yi) == rec.NOT_FOUND)
			rec.emplace_shadow(yi, i);
	base = mpow(mpow(y, p - 2, p), rem, p);
}
int BSGS(int z, int p) {
	for (int i = 0; i < lim; ++i, z = (LL)z * base % p) {
		int res = rec.find(z);
		if (res != rec.NOT_FOUND)
			return i * rem + res;
	}
	return -1;
}
