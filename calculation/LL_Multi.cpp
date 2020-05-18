//O(1). mod can't be too small. sizeof(long double) > 8
inline long long multi(long long x,long long y,long long mod)
{
    long long tmp=(x*y-(long long)((long double)x/mod*y+1.0e-8)*mod);
    return tmp<0 ? tmp+mod : tmp;
}

template <typename T>
void AddMod(T& x, T p) {
    if (x >= p)
        x -= p;
}
template <typename T>
void SubMod(T& x, T p) {
    if (x < 0)
        x += p;
}
//O(log)
template <typename T>
T mul(T a, T b, T p) {
    T ans = 0;
    SubMod(a %= p, p);
    SubMod(b %= p, p);
    while (b) {
        if (b & 1)
            AddMod(ans += a, p);
        b >>= 1;
        AddMod(a += a, p);
    }
    return ans;
}
