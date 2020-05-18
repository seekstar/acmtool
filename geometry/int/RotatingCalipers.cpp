//Assume that ps is convex and anticlockwise
LT SquareOfDiameterOfConvex(const VEC ps[], int n) {
    if (n < 2) return 0;
    if (2 == n) return ps[0].dist2(ps[1]);

    LT ans = 0;
    for (int i = 0, j = 2, j1 = Add(3, n); i < n; ++i) {
        int i1 = Add(i + 1, n);
        VEC now = ps[i1] - ps[i];
        while ((now ^ (ps[j] - ps[i])) <= (now ^ (ps[j1] - ps[i])))
            j = j1, j1 = Add(j + 1, n);
        ans = max(ans, max(ps[j].dist2(ps[i]), ps[j].dist2(ps[i1])));
    }
    return ans;
}
