//return NumOfLatticePoints - 1
LT OnEdge_1(const VEC& p1, const VEC& p2) {
    return GCD(abs(p1.x - p2.x), abs(p1.y - p2.y));
}
LT OnPoly(const VEC ps[], int n) {
    LT ans = OnEdge_1(ps[0], ps[n-1]);
    for (int i = 1; i < n; ++i)
        ans += OnEdge_1(ps[i], ps[i-1]);
    return ans;
}
LT InPoly(const VEC ps[], int n) {
    return (abs(area2_di(ps, n)) - OnPoly(ps, n) + 2) >> 1;
}
