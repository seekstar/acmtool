//ls is anticlockwise
template <typename LINE>
bool InsideConvex(const VEC& p, const LINE ls[], int n) {
    int i;
    for (i = 0; i < n && ls[i].relation(p) == -1; ++i);
    return i == n;
}
//1: The line cross the inside of the convex hull
//0: otherwise
bool CrossConvex_inside(const SEG& b, const SEG sgs[], int n) {
    if (InConvex_inside(b.s, sgs, n) || InConvex_inside(b.e, sgs, n)) return true;
    int i = 0;
    for (; i < n; ++i) {
        int rel = b.Cross(sgs[i]);
        if (2 == rel) break;
        if (1 == rel) {
            VEC d = b.v * 1e-5;
            if (InConvex_inside(b.s + d, sgs, n) || InConvex_inside(b.e - d, sgs, n)) break;
        }
    }
    return i != n;
}

//O(log n)
namespace CrossConvex {
    double a[MAXN];
    //[0, 2*pi)
    double GetAngle(const VEC& b) {
        double x = atan2(b.y, b.x);
        return x < 0 ? x + 2 * pi : x;
    }
    void pre(const VEC ps[], int n) {
        if (n) a[n-1] = GetAngle(ps[0] - ps[n-1]);
        for (int i = 0; i < n - 1; ++i)
            a[i] = GetAngle(ps[i + 1] - ps[i]);
    }
    int find(double x, int n) {
        return (upper_bound(a, a + n, x) - a) % n;
    }
    bool check(const LINE& b, const VEC ps[], int n) {
        if (0 == n) return false;
        //auto find = [=](double x) {return (upper_bound(a, a + n, x) - a) % n; };
        double angle = GetAngle(b.v);
        const VEC& p1 = ps[find(angle, n)], p2 = ps[find(fmod((angle + pi), 2 * pi), n)];
        return b.relation(p1) * b.relation(p2) < 0;
    }
}
