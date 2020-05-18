//The points in ans[] start from the bottom left, and rotate anticlockwise.
//O(nlog n)
int GetConvex(VEC ans[], VEC ps[], int n) {
    sort(ps, ps + n);
    int t = -1;
    for (int i = 0; i < n; ++i) {
        while (t > 0 && !(ans[t] - ans[t-1]).ToLeftTest(ps[i] - ans[t]))
            --t;
        ans[++t] = ps[i];
    }
    int down = t;
    for (int i = n - 2; i >= 0; --i) {
        while (t > down && !(ans[t] - ans[t-1]).ToLeftTest(ps[i] - ans[t]))
            --t;
        ans[++t] = ps[i];
    }
    if (n > 1) --t;
    if (2 == t && ans[0] == ans[1]) --t;
    return t + 1;
}


struct POINT : VEC {
    int id;
};
//O(nlog n)
int GetConvex_parallel(bool dup[], POINT ans[], POINT ps[], int len, int n) {
    static bool in[MAXN];
    memset(in, 0, n * sizeof(bool));
    memset(dup, 0, n * sizeof(bool));
    sort(ps, ps + len);
    int t = 0;
    for (int i = 1; i < len; ++i) {
        if (ps[i] == ps[t]) {
            dup[ps[i].id] = dup[ps[t].id] = true;
        } else {
            ps[++t] = ps[i];
        }
    }
    len = t + 1;

    t = -1;
    for (int i = 0; i < len; ++i) {
        while (t > 0 && (ans[t] - ans[t-1]).ToRightTest(ps[i] - ans[t]))
            in[ans[t--].id] = false;
        in[(ans[++t] = ps[i]).id] = true;
    }
    int down = t;
    for (int i = len - 2; i >= 0; --i) {
        if (in[ps[i].id] && i) continue;    //Need the first on to adjust
        while (t > down && (ans[t] - ans[t-1]).ToRightTest(ps[i] - ans[t]))
            in[ans[t--].id] = false;
        in[(ans[++t] = ps[i]).id] = true;
    }
    if (t > 1 && ans[t] == ps[0]) --t;
    return t + 1;
}
