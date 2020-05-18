inline UnsignedBigInt BigTens(int n) const {
    UnsignedBigInt ans;
    ans.s.resize(n / WIDTH + 1, 0);
    ans.s[n / WIDTH] = tens[n % WIDTH];
    return ans;
}

UnsignedBigInt mpow(UnsignedBigInt base, UnsignedBigInt ex, const UnsignedBigInt& p) {
    UnsignedBigInt ans(1);
    while (ex) {
        int rem = ex.DivEq_Mod(2);
        if (rem)
            (ans *= base) %= p;
        if (ex) {
            (base *= base) %= p;
        }
    }
    return ans;
}

