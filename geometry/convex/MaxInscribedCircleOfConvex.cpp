const double maxx = 10000;
double MaxInscribedCircleOfConvex(const LINE ls[], int n, double err) {
    static VEC inc[MAXN];
    static LINE nls[MAXN];
    for (int i = 0; i < n; ++i) {
        inc[i] = ls[i].v.rotleft().norm();
        nls[i].v = ls[i].v;
    }
    double L = 0, R = maxx;
    while (fabs(R - L) > err) {
        double mid = (L + R) / 2;
        for (int i = 0; i < n; ++i)
            nls[i].s = ls[i].s + inc[i] * mid;
        if (HalfPlane::Intersection(nls, n)) {
            L = mid;
        } else {
            R = mid;
        }
    }
    return (L + R) / 2;
}