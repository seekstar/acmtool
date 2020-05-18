struct SGT {
    //const static int max_node = MAXN2 << 2;
    bool s[max_node];

    void Init(int n) {
        memset(s, 0, (n<<2) * sizeof(s[0]));
    }
    void Reverse(int rt, int l, int r, int L, int R) {
        if (L <= l && r <= R) {
            s[rt] = !s[rt];
        } else {
            int mid = (l + r) >> 1;
            if (L <= mid) Reverse(ls(rt), l, mid, L, R);
            if (mid < R) Reverse(rs(rt), mid+1, r, L, R);
        }
    }
    bool Query(int rt, int l, int r, int x) {
        if (l == r) {
            return s[rt];
        } else {
            int mid = (l + r) >> 1;
            if (x <= mid) return s[rt] ^ Query(ls(rt), l, mid, x);
            else return s[rt] ^ Query(rs(rt), mid+1, r, x);
        }
    }
};
struct SGT2 {
    //const static int max_node = MAXN1 << 2;
    SGT s[max_node];
    int n2;

    void Init(int n1, int _n2) {
        n2 = _n2;
        for (int i = 0; i <= (n1 << 2); ++i)
            s[i].Init(n2);
    }
    void Reverse(int rt, int l, int r, int L1, int R1, int L2, int R2) {
        if (L1 <= l && r <= R1) {
            s[rt].Reverse(1, 1, n2, L2, R2);
        } else {
            int mid = (l + r) >> 1;
            if (L1 <= mid) Reverse(ls(rt), l, mid, L1, R1, L2, R2);
            if (mid < R1) Reverse(rs(rt), mid+1, r, L1, R1, L2, R2);
        }
    }
    bool Query(int rt, int l, int r, int x1, int x2) {
        bool ans = s[rt].Query(1, 1, n2, x2);
        if (l != r) {
            int mid = (l + r) >> 1;
            if (x1 <= mid) ans ^= Query(ls(rt), l, mid, x1, x2);
            else ans ^= Query(rs(rt), mid+1, r, x1, x2);
        }
        return ans;
    }
};
