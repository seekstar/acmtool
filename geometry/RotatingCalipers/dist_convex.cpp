//If cross, return 0  ???
//The two convex mustn't include each other
double dist_convex(const VEC p1[], int n1, const VEC p2[], int n2, int sp2) {
    double ans = numeric_limits<double>::max();
    int j = sp2, j1 = Add(j + 1, n2);
    for (int i = 0; i < n1; ++i) {
        SEG now(p1[i], p1[Add(i + 1, n1)]);
        while (!now.v.ToLeftTest(p2[j] - p2[j1]))
            j = j1, j1 = Add(j + 1, n2);
        ans = min(ans, now.dist(SEG(p2[j], p2[j1])));
    }
    return ans;
}