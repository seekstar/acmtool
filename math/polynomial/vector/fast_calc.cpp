//O(n log^2 n)
inline int ls(int rt) {
    return rt << 1;
}
inline int rs(int rt) {
    return rt << 1 | 1;
}
void GetP(vi P[], int rt, int l, int r, const int x[]) {
    if (l == r) {
        P[rt].resize(2);
        P[rt][0] = Sub(-x[l], p);
        P[rt][1] = 1;
    } else {
        int mid = (l + r) >> 1;
        GetP(P, ls(rt), l, mid, x);
        GetP(P, rs(rt), mid+1, r, x);
        Mul_keep(P[rt], P[ls(rt)], P[rs(rt)]);
    }
}
void fast_calc(int ans[], int rt, int l, int r, const vi& a, const int x[], vi P[]) {
    static vi Q(MAXM);
    if (r - l < 100) {
        for (; l <= r; ++l) {
            ans[l] = 0;
            for (int j = a.size() - 1; j >= 0; --j)
                ans[l] = ((LL)ans[l] * x[l] + a[j]) % p;
        }
    } else {
        int mid = (l + r) >> 1;
        vi F;
        DivMod(Q, F, a, P[ls(rt)]);
        fast_calc(ans, ls(rt), l, mid, F, x, P);
        DivMod(Q, F, a, P[rs(rt)]);
        fast_calc(ans, rs(rt), mid+1, r, F, x, P);
    }
}
void fast_calc(int ans[], const vi& a, const int x[], int m) {
    static vector<int> P[MAXM << 2];
    GetP(P, 1, 0, m-1, x);
    fast_calc(ans, 1, 0, m-1, a, x, P);
}

