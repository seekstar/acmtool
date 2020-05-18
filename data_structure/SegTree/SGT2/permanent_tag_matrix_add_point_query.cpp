struct SGT {
    const static int max_node = MAXN2 << 2;
    int s[max_node];

    void Init(int n) {
        memset(s, 0, (n << 2) * sizeof(int));
    }
    void Add(int rt, int l, int r, int L, int R, int v) {
        if (L <= l && r <= R) {
            s[rt] += v;
        } else {
            int mid = (l + r) >> 1;
            if (L <= mid) Add(ls(rt), l, mid, L, R, v);
            if (mid < R) Add(rs(rt), mid+1, r, L, R, v);
        }
    }
    int Query(int rt, int l, int r, int x) {
        int ans = s[rt];
        if (l != r) {
            int mid = (l + r) >> 1;
            if (x <= mid) ans += Query(ls(rt), l, mid, x);
            else ans += Query(rs(rt), mid+1, r, x);
        }
        return ans;
    }
};
struct SGT2 {
    const static int max_node = MAXN1 << 2;
    SGT s[max_node];
    int n2;

    void Init(int n1, int _n2) {
        n2 = _n2;
        for (int i = 0, r = n2 << 2; i < r; ++i)
            s[i].Init(n2);
    }
    void Add(int rt, int l, int r, int L1, int R1, int L2, int R2, int v) {
        if (L1 <= l && r <= R1) {
            s[rt].Add(1, 1, n2, L2, R2, v);
        } else {
            int mid = (l + r) >> 1;
            if (L1 <= mid) Add(ls(rt), l, mid, L1, R1, L2, R2, v);
            if (mid < R1) Add(rs(rt), mid+1, r, L1, R1, L2, R2, v);
        }
    }
    int Query(int rt, int l, int r, int x1, int x2) {
        int ans = s[rt].Query(1, 1, n2, x2);
        if (l != r) {
            int mid = (l + r) >> 1;
            if (x1 <= mid) ans += Query(ls(rt), l, mid, x1, x2);
            else ans += Query(rs(rt), mid+1, r, x1, x2);
        }
        return ans;
    }
};
