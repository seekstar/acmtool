//convex
LT MaxArea2OfTriangle(VEC ps[], int n) {
    LT ans = 0;
    for (int i = 0; i < n-2; ++i) {
        int k = i + 2, k1 = Add(k + 1, n);
        for (int j = i + 1; j < n; ++j) {
            while (ps[j].cross(ps[k1], ps[i]) >= ps[j].cross(ps[k], ps[i]))
                k = k1, k1 = Add(k + 1, n);
            ans = max(ans, ps[j].cross(ps[k], ps[i]));
        }
    }
    return ans;
}
