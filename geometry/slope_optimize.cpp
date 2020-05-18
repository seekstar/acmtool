//SPLAY set
int lower_bound_slope(double k) {
        int rt = root, nxt, ans = root;
        while (1) {
            if ((nxt = PreOrNxt(rt, true))) {
                VEC d = keys[nxt] - keys[rt];
                if (sgn(d.y - k * d.x) <= 0) {
                    ans = rt;
                    rt = ls(rt);
                } else {
                    rt = rs(rt);
                }
            } else if ((nxt = PreOrNxt(rt, false))) {
                VEC d = keys[rt] - keys[nxt];
                if (sgn(d.y - k * d.x) <= 0) {
                    rt = ls(rt);
                } else {
                    ans = rt;
                    rt = rs(rt);
                }
            } else {
                break;
            }
        }
        return ans;
    }

template <class XSGN>
struct HalfConvexHull {
#define xsgn XSGN()
    struct CMPX {
        bool operator () (const VEC& a, const VEC& b) const {
            return xsgn(a.x - b.x) < 0;
        }
    };
    SPLAY<VEC, CMPX> s;

    void Init() {
        s.Init();
    }
    int Pre(int it) {
        return s.PreOrNxt(it, false);
    }
    int Nxt(int it) {
        return s.PreOrNxt(it, true);
    }

    int it;
    //The convex mustn't be degenerate
    //0: out
    //1: on
    //2: in
    int relation(const VEC& p) {
        it = s.lower_bound(p, true);
        if (it == s.end()) return 0;
        if (it == s.begin()) {
            if (xsgn(p.x - s.keys[it].x) < 0) return 0;
            else return xsgn(p.y - s.keys[it].y) + 1;
        }
        int bef = Pre(it);
        return sgn((s.keys[it] - s.keys[bef]) ^ (p - s.keys[bef])) + 1;
    }
    void Insert(const VEC& p) {
        if (relation(p)) return;
        if (it && sgn(s.keys[it].x - p.x) == 0) {
            s.erase(it);
        }
        s.Insert(p);
        it = s.root;    //The new node
        auto pre = Pre(it), nxt = Nxt(it);
        if (pre) {
            for (auto j = Pre(pre); j && sgn((s.keys[pre] - p) ^ (s.keys[j] - p)) >= 0; pre = j, j = Pre(j)) {
                s.erase(pre);
            }
        }
        if (nxt) {
            for (auto j = Nxt(nxt); j && sgn((s.keys[j] - p) ^ (s.keys[nxt] - p)) >= 0; nxt = j, j = Nxt(j)) {
                s.erase(nxt);
            }
        }
    }
};
