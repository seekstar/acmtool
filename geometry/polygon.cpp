//Anticlockwise is plus
double area_di(const VEC ps[], int n) {
    double ans = ps[n-1] ^ ps[0];
    for (int i = 0; i < n-1; ++i)
        ans += ps[i] ^ ps[i + 1];
    return ans / 2.0;
}
//1: anticlockwise
//0: otherwise
bool dir(const VEC ps[], int n) {
    return sgn(area_di(ps, n)) > 0;
}

//0: outside
//1: On the boundary(including vertex)
//2: Inside
int IsIn(const VEC& p, const VEC ps[], int n) {
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        int i1 = Add(i + 1, n);
        if (SEG(ps[i1], ps[i]).OnSeg(p)) return 1;
        int k = (ps[i1] - ps[i]) ^ (p - ps[i]);
        int d1 = ps[i].y - p.y;
        int d2 = ps[i1].y - p.y;
        if (k > 0 && d1 <= 0 && d2 > 0) ++cnt;
        if (k < 0 && d2 <= 0 && d1 > 0) --cnt;
    }
    return cnt ? 2 : 0;
}

//If area is 0, return (0, 0)
VEC barycenter(const VEC ps[], int n) {
    VEC ans{0, 0};
    double area = 0;
    for (int i = 1; i < n - 1; ++i) {
        double tmp = (ps[i] - ps[0]) ^ (ps[i+1] - ps[0]);
        area += tmp;
        ans = ans + (ps[0] + ps[i] + ps[i+1]) * (tmp / 3.0);
    }
    if (sgn(area)) ans = ans / area;
    return ans;
}
