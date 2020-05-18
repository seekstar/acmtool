template <typename T>
int mpow(int base, T ex, int p) {
    int ans = 1;
    for (; ex; ex >>= 1, base = (LL)base * base % p)
        if (ex & 1)
            ans = (LL)ans * base % p;
    return ans;
}
