//dynamic
namespace ConvexHull {
    VEC base;
    struct CMP {
        bool operator () (VEC a, VEC b) const {
            a = a - base;
            b = b - base;
            double d = atan2(a.y, a.x) - atan2(b.y, b.x);
            return fabs(d) < eps ? a.len2() < b.len2() : d < 0;
        }
    };

    set<VEC, CMP> s;
    typedef set<VEC>::iterator IT;

    void Init(const VEC& a, const VEC& b, const VEC& c) {
        base = (a + b + c) / 3.0;
        s.clear();
        s.insert(a);
        s.insert(b);
        s.insert(c);
    }
    IT Pre(IT it) {
        if (it == s.begin()) it = s.end();
        return --it;
    }
    IT Nxt(IT it) {
        if (++it == s.end()) it = s.begin();
        return it;
    }
	//The convex mustn't be degenerate
    //0: out
    //1: on
    //2: in
    int relation(const VEC& p) {
        auto it = s.lower_bound(p);
        if (it == s.end())
            it = s.begin();
        auto pre = *Pre(it);
        double res = (p - pre) ^ (*it - pre);
        if (res > eps) return 0;
        if (res < -eps) return 2;
        return 1;
    }
    void Insert(const VEC& p) {
        if (relation(p)) return;
        auto at = s.insert(p).first;
        auto it = Nxt(at);
        auto nxt = Nxt(it);
        while (s.size() > 3 && ((p - *nxt) ^ (*it - *nxt)) < eps) {
            s.erase(it);
            it = nxt;
            nxt = Nxt(it);
        }
        it = Pre(at);
        nxt = Pre(it);
        while (s.size() > 3 && ((*it - p) ^ (*nxt - p)) > -eps) {
            s.erase(it);
            it = nxt;
            nxt = Pre(it);
        }
    }
}
