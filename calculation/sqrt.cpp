template<typename T>
T MySqrt(T x) {
    T ans = 0;
    T bit;
    for(bit = 1; (LL)bit * bit <= x; bit <<= 1);

    while(bit >>= 1) {
        T tmp = ans | bit;
        if((LL)tmp * tmp <= x)
            ans = tmp;
    }

    return ans;
}

//return x^e <= rhs
bool LessEqPow(INT x, INT e, INT rhs) {
    LL ans = 1;
    while (e--) {
        ans *= x;
        if (ans > rhs)
            return false;
    }
    return true;
}
//floor(a^(1/x))
INT sqrt_floor(INT a, INT x) {
    INT L = 1, R = a;
    while (L <= R) {
        INT mid = (L + R) >> 1;
        if (LessEqPow(mid, x, a)) {
            L = mid + 1;
        } else {
            R = mid - 1;
        }
    }
    return L - 1;
}


