//Assume that ps is convex and anticlockwise
double minRectangleCover(const VEC ps[], int n) {
    if (n < 3) return 0;
    double ans = numeric_limits<double>::max();
    int u = 1, l, r = 1;    //up, left, right
    for (int i = 0, u1 = 2, l1, r1 = 2; i < n; ++i) {
        int i1 = Add(i + 1, n);
        VEC now = ps[i1] - ps[i];
        while (sgn((now ^ (ps[u] - ps[i])) - (now ^ (ps[u1] - ps[i]))) <= 0)
            u = u1, u1 = Add(u + 1, n);
        while (sgn((now * (ps[r] - ps[i])) - (now * (ps[r1] - ps[i]))) <= 0)
            r = r1, r1 = Add(r + 1, n);
        if (0 == i) l = r, l1 = Add(l + 1, n);
        while (sgn((now * (ps[i] - ps[l])) - (now * (ps[i] - ps[l1]))) <= 0)
            l = l1, l1 = Add(l + 1, n);
        ans = min(ans, (now ^ (ps[u] - ps[i])) * (now.rotleft() ^ (ps[l] - ps[r])) / now.len2());
    }
    return ans;
}
