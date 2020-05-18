namespace HalfPlane {
    //No same line
    //-2: reverse
    int di(const LINE& a, const LINE& b) {
        int rel = a.v.relation(b.v);
        if (0 == rel) {
            if (a.v.SameDi(b.v)) {
                return a.relation(b.s);
            } else {
                return -2;
            }
        } else {
            return rel;
        }
    }
    bool Infinite(const LINE ls[], int n) {
        stack<int> sta;
        LINE s = ls[0];
        LINE t = -ls[0];
        for (int i = 1; i < n; ++i) {
            int rel = di(s, ls[i]);
            if (-2 == rel) {
                sta.push(i);
            } else if (rel < 0) {
                s = ls[i];
                if (di(t, s) < 0)
                    return false;
            } else if (rel > 0) {
                rel = di(t, -ls[i]);
                if (rel > 0) {
                    t = -ls[i];
                    if (di(s, t) > 0)
                        return false;
                }
            }
        }
        while (!sta.empty()) {
            int i = sta.top();
            sta.pop();
            if (0 == ls[i].v.relation(s.v)) {
                if (s.relation(ls[i].s) <= 0) {
                    s.s = ls[i].s;
                } else {
                    return false;
                }
            } else if (ls[i].v.relation(t.v) || t.relation(ls[i].s) < 0) {
                return false;
            }
        }
        if (s.v.relation(t.v)) {
            return true;
        } else {
            if (s.v.SameDi(-t.v)) return true;
            else return s.relation(t.s) <= 0;
        }
    }

    int que[MAXN];
    VEC cp[MAXN];    //Cross points
    int st, ed;

    //0: The area is 0
    //1: Can construct a convex polygon
    //2: The area is infinite
    int Intersection(const LINE ls[], int n) {
        static pair<double, int> ord[MAXN];

		if (Infinite(ls, n)) return 2;
        for (int i = 0; i < n; ++i)
            ord[i] = make_pair(atan2(ls[i].v.y, ls[i].v.x), i);
        sort(ord, ord + n);
        int m = 0;
        for (int i = 1; i < n; ++i)
            if (sgn(ord[i].first - ord[m].first))
                ord[++m] = ord[i];
            else if (ls[ord[m].second].relation(ls[ord[i].second].s) == -1)
                ord[m] = ord[i];
        n = m + 1;

        que[st=0] = ord[0].second;
        que[ed=1] = ord[1].second;
        cp[1] = ls[ord[1].second].CrossPoint(ls[ord[0].second]);
        for (int i = 2; i < n; ++i) {
            const LINE &now = ls[ord[i].second];
            while (st < ed && now.relation(cp[ed]) == 1)
                --ed;
            while (st < ed && now.relation(cp[st + 1]) == 1)
                ++st;
            if (now.v.relation(ls[que[ed]].v) == 0) return 0;
            que[++ed] = ord[i].second;
            cp[ed] = now.CrossPoint(ls[que[ed - 1]]);
        }
        while (st < ed && ls[que[st]].relation(cp[ed]) == 1)
            --ed;
        while (st < ed && ls[que[ed]].relation(cp[st + 1]) == 1)
            ++st;
        return st + 1 < ed;
    }
    void GetConvex(VEC ps[], int& n, const LINE ls[]) {
        n = ed - st + 1;
        memcpy(ps, cp + st, n * sizeof(VEC));
    }
}
