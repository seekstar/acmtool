struct LAZY {
    int v, l, r;
};
#define MAX_NODE1 (MAXN << 2)
#define MAX_NODE2 (MAXM << 2)
struct SGT2 {
    int s[MAX_NODE1][MAX_NODE2], n1, n2;
    LAZY lazy1[MAX_NODE1];
    int lazy2[MAX_NODE1][MAX_NODE2];

    inline int ls(int rt) {
        return rt << 1;
    }
    inline int rs(int rt) {
        return rt << 1 | 1;
    }
    void Init(int _n1, int _n2) {
        n1 = _n1;
        n2 = _n2;
        memset(lazy1, 0, ((n1 << 2)+1) * sizeof(int));
        for (int i = 0; i <= (n1 << 2); ++i) {
            memset(s[i], 0, (n2 << 2) * sizeof(int));
            memset(lazy2[i], 0, (n2 << 2) * sizeof(int));
        }
    }
    void Init(int _n1, int _n2, int a[][MAXM]) {
        n1 = _n1;
        n2 = _n2;
        Build1(1, 1, n1, a);
    }
    void PushUp(int d, int rt) {
        s[d][rt] = s[d][ls(rt)] + s[d][rs(rt)];
    }
    void Build2(int d, int rt, int l, int r, int a[MAXM]) {
        if (l == r) {
            s[d][rt] = a[l];
        } else {
            int mid = (l + r) >> 1;
            Build2(d, ls(rt), l, mid, a);
            Build2(d, rs(rt), mid+1, r, a);
            PushUp(d, rt);
        }
        lazy2[d][rt] = 0;
    }
    void Build1(int rt, int l, int r, int a[][MAXM]) {
        if (l == r) {
            Build2(rt, 1, 1, n2, a[l]);
        } else {
            int mid = (l + r) >> 1;
            Build1(ls(rt), l, mid, a);
            Build1(rs(rt), mid+1, r, a);
            for (int i = 1; i <= (n2 << 2); ++i)
                s[rt][i] = s[ls(rt)][i] + s[rs(rt)][i];
        }
        lazy1[rt] = LAZY{0, 0, 0};
    }
    void PushDown2(int d, int rt, int l, int mid, int r) {
        if (lazy2[d][rt]) {
            lazy2[d][ls(rt)] += lazy2[d][rt];
            lazy2[d][rs(rt)] += lazy2[d][rt];
            s[d][ls(rt)] += lazy2[d][rt] * (mid - l + 1);
            s[d][rs(rt)] += lazy2[d][rt] * (r - mid);
            lazy2[d][rt] = 0;
        }
    }
    void Add2(int d, int rt, int l, int r, int L, int R, int v) {
        if (L <= l && r <= R) {
            s[d][rt] += (r - l + 1) * v;
            lazy2[d][rt] += v;
        } else {
            int mid = (l + r) >> 1;
            PushDown2(d, rt, l, mid, r);
            if (L <= mid) Add2(d, ls(rt), l, mid, L, R, v);
            if (mid < R) Add2(d, rs(rt), mid+1, r, L, R, v);
            PushUp(d, rt);
        }
    }
    void PushDown1(int rt, int l, int mid, int r) {
        int& v = lazy1[rt].v, L = lazy1[rt].l, R = lazy1[rt].r;
        if (v) {
            lazy1[ls(rt)].v += v;
            lazy1[rs(rt)].v += v;
            Add2(ls(rt), 1, 1, n2, L, R, v * (mid - l + 1));
            Add2(rs(rt), 1, 1, n2, L, R, v * (r - mid));
            v = 0;
        }
    }
    //return the width that is modified
    int Add1(int rt, int l, int r, int L1, int R1, int L2, int R2, int v) {
        int cnt = 0;
        if (L1 <= l && r <= R1) {
            cnt = r - l + 1;
			PushDown1(rt, l, (l + r) >> 1, r);
			lazy1[rt] = LAZY{v, L2, R2};
        } else {
            int mid = (l + r) >> 1;
            PushDown1(rt, l, mid, r);
            if (L1 <= mid) cnt = Add1(ls(rt), l, mid, L1, R1, L2, R2, v);
            if (mid < R1) cnt += Add1(rs(rt), mid+1, r, L1, R1, L2, R2, v);
        }
        Add2(rt, 1, 1, n2, L2, R2, v * cnt);
        return cnt;
    }
    
    int Sum1(int rt, int l, int r, int L1, int R1, int L2, int R2) {
        if (L1 <= l && r <= R1) {
            return Sum2(rt, 1, 1, n2, L2, R2);
        } else {
            int ans = 0, mid = (l + r) >> 1;
            PushDown1(rt, l, mid, r);
            if (L1 <= mid) ans = Sum1(ls(rt), l, mid, L1, R1, L2, R2);
            if (mid < R1) ans += Sum1(rs(rt), mid+1, r, L1, R1, L2, R2);
            return ans;
        }
    }
    int Sum2(int d, int rt, int l, int r, int L, int R) {
        if (L <= l && r <= R) {
            return s[d][rt];
        } else {
            int ans = 0, mid = (l + r) >> 1;
            PushDown2(d, rt, l, mid, r);
            if (L <= mid) ans = Sum2(d, ls(rt), l, mid, L, R);
            if (mid < R) ans += Sum2(d, rs(rt), mid+1, r, L, R);
            return ans;
        }
    }
};

