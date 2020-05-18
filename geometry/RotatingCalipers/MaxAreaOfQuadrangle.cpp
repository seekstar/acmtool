//O(n^2)
//ps is convex
double MaxAreaOfQuadrangle(const VEC ps[], int n) {
    double ans = 0;
    if (n >= 4) {
        LINE now;
        for (int i = 0; i < n - 3; ++i) {
            now.s = ps[i];
            int l = i + 3, r = i + 1, l1 = Add(l + 1, n), r1 = Add(r + 1, n);
            for (int j = i + 2; j < n - 1; ++j) {
                now.v = ps[j] - ps[i];
                while (now.dist(ps[l1]) >= now.dist(ps[l]))
                    l = l1, l1 = Add(l + 1, n);
                while (now.dist(ps[r1]) >= now.dist(ps[r]))
                    r = r1, r1 = Add(r + 1, n);
                ans = max(ans, (now.v ^ (ps[l] - ps[i])) + ((ps[r] - ps[i]) ^ now.v));
            }
        }
    }
    return ans / 2.0;
}