//pure
struct down_sgn {
    int operator () (LT x) const {
        return sgn(x);
    }
};
struct up_sgn {
    int operator () (LT x) const {
        return -sgn(x);
    }
};
template <class XSGN>
struct HalfConvexHull {
#define xsgn XSGN()
    struct CMPX {
        bool operator () (const VEC& a, const VEC& b) {
            return xsgn(a.x - b.x) < 0;
        }
    };
    typedef set<VEC, CMPX> SE;
    SE s;
    typedef typename SE::iterator IT;

    IT it;
    //The convex mustn't be degenerate
    //0: out
    //1: on
    //2: in
    int relation(const VEC& p) {
        it = s.lower_bound(p);
        if (it == s.end()) return 0;
        if (it == s.begin()) {
            if (xsgn(p.x - it->x) < 0) return 0;
            else return xsgn(p.y - it->y) + 1;
        }
        auto bef = it;
        --bef;
        return sgn((*it - *bef) ^ (p - *bef)) + 1;
    }
    IT Pre(IT it) {
        return it == s.begin() ? s.end() : --it;
    }
    void Insert(const VEC& p) {
        if (relation(p)) return;
        bool del = false;
        if (it != s.end() && it->x == p.x) {
            s.erase(it);
        }
        it = s.insert(p).first;
        auto pre = Pre(it);
        auto nxt(it);
        ++nxt;
        if (pre != s.end()) {
            for (auto j = Pre(pre); j != s.end() && ((*pre - p) ^ (*j - p)) >= 0; pre = j, j = Pre(j)) {
                s.erase(pre);
            }
        }
        if (nxt != s.end()) {
            auto j = nxt;
            for (++j; j != s.end() && ((*j - p) ^ (*nxt - p)) >= 0; nxt = j, ++j) {
                s.erase(nxt);
            }
        }
    }
};
struct ConvexHull {
    HalfConvexHull<down_sgn> down;
    HalfConvexHull<up_sgn> up;
    int relation(const VEC& p) {
        int r = down.relation(p);
        if (r != 2) return r;
        return up.relation(p);
    }
    void Insert(const VEC& p) {
        down.Insert(p);
        up.Insert(p);
    }
};


//area2
template <class XSGN>
struct HalfConvexHull {
#define xsgn XSGN()
    struct CMPX {
        bool operator () (const VEC& a, const VEC& b) {
            return xsgn(a.x - b.x) < 0;
        }
    };
    typedef set<VEC, CMPX> SE;
    SE s;
    typedef typename SE::iterator IT;

    LT area2;   //to (0, 0)
    IT it;
    HalfConvexHull() : area2(0) {}
    //The convex mustn't be degenerate
    //0: out
    //1: on
    //2: in
    int relation(const VEC& p) {
        it = s.lower_bound(p);
        if (it == s.end()) return 0;
        if (it == s.begin()) {
            if (xsgn(p.x - it->x) < 0) return 0;
            else return xsgn(p.y - it->y) + 1;
        }
        auto bef = it;
        --bef;
        return sgn((*it - *bef) ^ (p - *bef)) + 1;
    }
    IT Pre(IT it) {
        return it == s.begin() ? s.end() : --it;
    }
    void Insert(const VEC& p) {
        if (relation(p)) return;
        bool del = false;
        VEC d;
        if (it != s.end() && it->x == p.x) {
            d = *it;
            del = true;
            s.erase(it);
        }
        it = s.insert(p).first;
        auto pre = Pre(it);
        auto nxt(it);
        ++nxt;
        if (pre != s.end()) {
            if (del) {
                area2 -= *pre ^ d;
            } else if (nxt != s.end()) {
                area2 -= *pre ^ *nxt;
            }
            area2 += *pre ^ p;
            for (auto j = Pre(pre); j != s.end() && ((*pre - p) ^ (*j - p)) >= 0; pre = j, j = Pre(j)) {
                area2 += (*j ^ p) - (*j ^ *pre) - (*pre ^ p);
                s.erase(pre);
            }
        }
        if (nxt != s.end()) {
            if (del) {
                area2 -= d ^ *nxt;
            }
            area2 += p ^ *nxt;
            auto j = nxt;
            for (++j; j != s.end() && ((*j - p) ^ (*nxt - p)) >= 0; nxt = j, ++j) {
                area2 += (p ^ *j) - (p ^ *nxt) - (*nxt ^ *j);
                s.erase(nxt);
            }
        }
    }
};
struct ConvexHull {
    HalfConvexHull<down_sgn> down;
    HalfConvexHull<up_sgn> up;
    void Insert(const VEC& p) {
        down.Insert(p);
        up.Insert(p);
    }
    LT area2() const {
        if (down.s.empty()) return 0;
        return (*up.s.rbegin() ^ *down.s.begin()) + down.area2 +
               (*down.s.rbegin() ^ *up.s.begin()) + up.area2;
    }
};



//SPLAY set
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
        if (it && s.keys[it].x == p.x) {
            s.erase(it);
        }
        s.Insert(p);
        it = s.root;    //The new node
        auto pre = Pre(it), nxt = Nxt(it);
        if (pre) {
            for (auto j = Pre(pre); j && ((s.keys[pre] - p) ^ (s.keys[j] - p)) >= 0; pre = j, j = Pre(j)) {
                s.erase(pre);
            }
        }
        if (nxt) {
            for (auto j = Nxt(nxt); j && ((s.keys[j] - p) ^ (s.keys[nxt] - p)) >= 0; nxt = j, j = Nxt(j)) {
                s.erase(nxt);
            }
        }
    }
};
struct ConvexHull {
    HalfConvexHull<down_sgn> down;
    HalfConvexHull<up_sgn> up;
    void Init() {
        down.Init();
        up.Init();
    }
    int relation(const VEC& p) {
        int r = down.relation(p);
        if (r != 2) return r;
        return up.relation(p);
    }
    void Insert(const VEC& p) {
        down.Insert(p);
        up.Insert(p);
    }
};

