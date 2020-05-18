bool On_horizon(const VEC& l, const VEC& r, const VEC& p) {
    return p == l || p == r || (p.y == l.y && p.y == r.y && l.x <= p.x && p.x <= r.x);
}
//O(log n)
//0: out
//1: on
//2: inside
int relation_convex(VEC ps[], int n, int sp, const VEC& p) {
    ps[n] = ps[0];
    if (On_horizon(ps[0], ps[1], p) || On_horizon(ps[sp+1], ps[sp], p)) return 1;
    if (p.y <= ps[0].y || p.y >= ps[sp].y) return 0;
    int mid = (ps[sp] - ps[0]).ToLeftTest(p - ps[0]) ?
              lower_bound_y(ps, sp, n, p.y, -1) :
              lower_bound_y(ps, 0, sp, p.y, 1);
    return 1 - (ps[mid] - ps[mid-1]).relation(p - ps[mid-1]);
}



//ls is anticlockwise
template <typename LINE>
bool InsideConvex(const VEC& p, const LINE ls[], int n) {
    int i;
    for (i = 0; i < n && ls[i].relation(p) == -1; ++i);
    return i == n;
}
bool OnConvex(const VEC& p, const SEG sgs[], int n) {
    int i;
    for (i = 0; i < n && !sgs[i].OnSeg(p); ++i);
    return i != n;
}
//0: outside
//1: on
//2: Inside
int relation(const VEC& p, const SEG sgs[], int n) {
    return InsideConvex(p, sgs, n) ? 2 : OnConvex(p, sgs, n);
}
void GetSegs(SEG sgs[], const VEC ps[], int n) {
    sgs[0] = SEG(ps[n-1], ps[0]);
    for (int i = 1; i < n; ++i)
        sgs[i] = SEG(ps[i-1], ps[i]);
}
//or inside or contact
bool Intersect_convex(const VEC p1[], int n1, const VEC p2[], int n2) {
    static SEG s1[MAXN], s2[MAXN];
    if (!n1 || !n2) return false;
    for (int i = 0; i < n1; ++i) {
        int i1 = (i + 1) % n1;
        SEG now(p1[i], p1[i1]);
        for (int j = 0; j < n2; ++j) {
            int j1 = (j + 1) % n2;
            if (now.Cross(SEG(p2[j], p2[j1])))
                return true;
        }
    }
    GetSegs(s1, p1, n1);
    GetSegs(s2, p2, n2);
    return relation(p1[0], s2, n2) || relation(p2[0], s1, n1);
}

