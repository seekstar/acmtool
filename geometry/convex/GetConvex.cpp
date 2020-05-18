struct CMP_POINT {
    VEC p;
    explicit CMP_POINT(const VEC& _p) : p(_p) {}
    bool operator () (const VEC& a, const VEC& b) {
        int d = sgn((a - p) ^ (b - p));
        return 0 == d ? a.dist(p) < b.dist(p) : d > 0;
    }
};
//O(nlog n)
int GetConvex(VEC ps[], int n) {
    if (n >= 2) {
        VEC mn = ps[0];
        for (int i = 1; i < n; ++i)
            mn = min(mn, ps[i]);
        sort(ps, ps + n, CMP_POINT(mn));
        int t = 1;
        for (int i = 2; i < n; ++i) {
            while (t && !(ps[t] - ps[t-1]).ToLeftTest(ps[i] - ps[t]))
                --t;
            ps[++t] = ps[i];
        }
        n = t + 1;
        if (2 == n && ps[0] == ps[1])
            --n;
    }
    return n;
}





struct POINT : VEC {
    int id;
};
//O(nlog n)
//n is the number of id
int GetConvex_parallel(bool dup[], POINT ans[], POINT ps[], int len, int n) {
    sort(ps, ps + len);
    memset(dup, 0, n * sizeof(bool));
    int k = 0;
    for (int i = 1; i < len; ++i) {
        if (ps[i] == ps[k]) {
            dup[ps[i].id] = dup[ps[k].id] = true;
        } else {
            ps[++k] = ps[i];
        }
    }
    len = k + 1;

    int t = 1;
    for (VEC line = ps[len-1] - ps[0]; t < len && (ps[t] - ps[0]).parallel(line); ++t);
    if (t == len) {
        memcpy(ans, ps, len * sizeof(POINT));
        return len;
    }
    t = -1;
    for (int i = 0; i < len; ++i) {
        while (t > 0 && (ans[t] - ans[t-1]).ToRightTest(ps[i] - ans[t]))
            --t;
        ans[++t] = ps[i];
    }
    int down = t;
    for (int i = len - 2; i >= 0; --i) {
        while (t > down && (ans[t] - ans[t-1]).ToRightTest(ps[i] - ans[t]))
            --t;
        ans[++t] = ps[i];
    }
    if (len > 1) --t;
    if (2 == t && ans[0] == ans[1]) --t;
    return t + 1;
}

