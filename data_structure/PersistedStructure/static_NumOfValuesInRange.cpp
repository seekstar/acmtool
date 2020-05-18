struct PST : public PST_base {
    //[L, R] can't be empty set!!!!
    //Get the number of values in the range [L, R] in the interval (a, b]
    int Query(int rt_a, int rt_b, int l, int r, int L, int R)
    {
        int ans = 0;
        if (L <= l && r <= R) {
            ans = data[rt_b] - data[rt_a];
        } else {
            int mid = (l + r) >> 1;
            if (L <= mid) ans += Query(lson[rt_a], lson[rt_b], l, mid, L, R);
            if (R > mid) ans += Query(rson[rt_a], rson[rt_b], mid+1, r, L, R);
        }
        return ans;
    }
};

