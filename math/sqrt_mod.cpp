#include <random>
int p, w;
default_random_engine e;
struct NUM {
    int x, y;
    NUM operator * (const NUM& rhs) const {
        return NUM{(int)Add((LL)x * rhs.x % p + (LL)y * rhs.y % p * w % p, p),
                   (int)Add((LL)x * rhs.y % p + (LL)y * rhs.x % p, p)};
    }
};
NUM mpow(NUM base, int ex) {
    NUM ans{1, 0};
    for (; ex; ex >>= 1, base = base * base)
        if (ex & 1)
            ans = ans * base;
    return ans;
}
//Return -1 if there is no solution
//If return x, then the other solution is p - x (they might be equal)
int sqrt(int a, int _p) {
    p = _p;
    a %= p;
    if (0 == a || 2 == p) return a;
    if (mpow(a, (p-1)>>1, p) == p-1) return -1;  //no solution
    int b;
    uniform_int_distribution<int> rand(0, p-1);
    do {
        b = rand(e);
        w = Sub((LL)b * b % p - a, p);
    } while (mpow(w, (p-1)>>1, p) != p-1);
    return mpow(NUM{b, 1}, (p + 1) >> 1).x;
}

