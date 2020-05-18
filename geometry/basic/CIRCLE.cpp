struct CIRCLE {
    VEC c;  //center
    double r;

	void SetCircumcircle(const VEC& A, const VEC& B) {
        c = (A + B) / 2.0;
        r = (B - A).len() / 2;
    }
    void SetCircumcircle(const VEC& A, VEC B, VEC C) {
        B = B - A;
        C = C - A;
        double s2di = B ^ C;
        VEC abv = B.rotleft() * s2di;
        VEC acv = C.rotleft() * (-s2di);
        VEC to = (abv * C.len2() + acv * B.len2()) / (2.0 * sq(s2di));
        c = A + to;
        r = to.len();
    }
    /*void SetCircumcircle(const VEC& A, const VEC& B, const VEC& C) {
        LINE u{(A + B) / 2, (B - A).rotleft()};
        LINE v{(B + C) / 2, (C - B).rotleft()};
        c = u.CrossPoint(v);
        r = c.dist(A);
    }*/
	void SetInscribedCircle(const VEC& A, const VEC& B, const VEC& C) {
        double la = (B - C).len(), lb = (A - C).len(), lc = (A - B).len(), sum = la + lb + lc;
        c = (A * la + B * lb + C * lc) / sum;
        r = ((B - A) ^ (C - A)).len() / sum;
    }
    /*void SetInscribedCircle(const VEC& A, const VEC& B, const VEC& C) {
        LINE u, v;
        u.SetAngularBisector(A, B, C);
        v.SetAngularBisector(B, A, C);
        c = u.CrossPoint(v);
        r = LINE(A, B - A).dist(c);
    }*/

    //-1: in
    //0: on
    //1: out
    int relation(const VEC& p) const {
        return sgn(c.dist(p) - r);
    }
    //-1: cross
    //0: tangent
    //1: away from
    int relation(const LINE& b) const {
        return sgn(b.dist(c) - r);
    }
	
    //1: inside
    //2: internally tangent
    //3: Cross
    //4: externally tangent
    //5: away from
    int relation(const CIRCLE& b) const {
        double d = c.dist(b.c);
        int s = sgn(d - fabs(b.r - r));
        if (s <= 0) return s + 2;
        return sgn(d - (b.r + r)) + 4;
    }
	
	int TangentLine(const VEC& p, LINE& L0, LINE& L1) const {
        int rel = relation(p);
        if (rel == -1) return 0;
        if (rel == 0) {
            L0 = LINE(p, (p - c).rotleft());
            return 1;
        }
        double d = c.dist(p), l = r * r / d;  //l / r = r / d
        VEC v0 = (c - p).norm(), h0 = v0.rotleft() * sqrt(sq(r) - sq(l));
        v0 = v0 * (d - l);
        L0 = LINE(p, v0 + h0);
        L1 = LINE(p, v0 - h0);
        return 2;
    }
	
	//p1 p2 is in the same direction of b.v
	int CrossPoint(const LINE& b, VEC& p1, VEC& p2) const {
        int rel = relation(b);
        if (1 == rel) return 0;
        VEC a = b.projection(c);
        if (0 == rel) {
            p1 = a;
            return 1;
        } else {
            VEC tmp = b.v.trunc(sqrt(sq(r) - sq(b.dist(c))));
            p1 = a - tmp;
            p2 = a + tmp;
            return 2;
        }
    }

    double CrossArea(const CIRCLE& b) const {
        int rel = relation(b);
        if (rel >= 4) return 0;
        if (rel <= 2) return min(area(), b.area());
        double d = c.dist(b.c), hf = (r + b.r + d) / 2.0, S = sqrt(hf * (hf - r) * (hf - b.r) * (hf - d));
        double a1 = acos((sq(r) + sq(d) - sq(b.r)) / (2.0 * r * d));
        double a2 = acos((sq(b.r) + sq(d) - sq(r)) / (2.0 * b.r * d));
        return a1 + a2 - S;
    }

    //The cross area of the circle and the triangle cab
    //If ab is anticlockwise, return plus ans.
    double CrossArea_di(const VEC& a, const VEC& b) const {
        static VEC ps[5];
        int len = 1;
        ps[0] = a;
        SEG L(a, b);
        if (2 == CrossPoint(L, ps[1], ps[2])) { //warning: use SEG as LINE
            if (L.exclusive_between(ps[1])) ps[len++] = ps[1];
            if (L.exclusive_between(ps[2])) ps[len++] = ps[2];
        }
        ps[len++] = b;
        for (int i = 0; i < len; ++i)
            ps[i] = ps[i] - c;
        double ans = 0;
        for (int i = 0; i < len-1; ++i) {
            if (sgn(ps[i].len() - r) > 0 || sgn(ps[i+1].len() - r) > 0)
                ans += r * r * ps[i].rad_di(ps[i+1]);
            else ans += ps[i] ^ ps[i+1];
        }
        return ans / 2.0;
    }
	//Anticlockwise is plus
    double CrossArea_di(const VEC ps[], int n) {
        double ans = CrossArea_di(ps[n-1], ps[0]);
        for (int i = 0; i < n-1; ++i)
            ans += CrossArea_di(ps[i], ps[i+1]);
        return ans;
    }


	//Return the number of points
    int CrossPoint(const CIRCLE& b, VEC& p1, VEC& p2) const {
        int rel = relation(b);
        if (1 == rel || 5 == rel) return 0;
        double d = c.dist(b.c);
        double l = (sq(d) + sq(r) - sq(b.r)) / (2 * d); //projection of r on d
        VEC v = (b.c - c).norm();
        VEC t = c + v * l;
        v = v.rotleft() * sqrt(sq(r) - sq(l));
        p1 = t + v;
        p2 = t - v;
        return 2 == rel || 4 == rel ? 1 : 2;
    }


	bool operator == (const CIRCLE& b) const {
        return c == b.c && sgn(r - b.r) == 0;
    }
    double area() const {
        return pi * sq(r);
    }
    double circumference() const {
        return 2 * pi * r;
    }
};

//Get the circles of radius r that pass a and b
int GetCircle(const VEC& a, const VEC& b, double r, CIRCLE& c1, CIRCLE& c2) {
    c1.r = c2.r = r;
    return CIRCLE(a, r).CrossPoint(CIRCLE(b, r), c1.c, c2.c);
}
//Get the circles of radius r that are tangent to u and pass p
int GetCircle(const LINE& u, const VEC& p, double r, CIRCLE cs[]) {
    cs[0].r = cs[1].r = r;
    VEC v = u.v.rotleft().trunc(r);
    CIRCLE c(p, r);
    int cnt = c.CrossPoint(LINE(u.s + v, u.v), cs[0].c, cs[1].c);
    if (cnt < 2) cnt += c.CrossPoint(LINE(u.s - v, u.v), cs[cnt].c, cs[cnt+1].c);
    return cnt;
}
//Get the circles of radius r that are tangent to both L0 and L1
int GetCircle(const LINE& L0, const LINE& L1, double r, CIRCLE cs[]) {
    if (L0.v.parallel(L1.v))
        return sgn(L0.dist(L1.s) - 2 * r) ? 0 : 0x3f3f3f3f;
    VEC v0 = L0.v.rotleft().trunc(r), v1 = L1.v.rotleft().trunc(r);
    for (int i = 0; i < 4; ++i)
        cs[i].r = r;
    LINE L00(L0.s + v0, L0.v), L01(L0.s - v0, L0.v), L10(L1.s + v1, L1.v), L11(L1.s - v1, L1.v);
    cs[0].c = L00.CrossPoint(L10);
    cs[1].c = L01.CrossPoint(L10);
    cs[2].c = L00.CrossPoint(L11);
    cs[3].c = L01.CrossPoint(L11);
    return 4;
}
//Assume that cc0 and cc1 do not intersect
//Get the circles of radius r that are tangent to both cc0 and cc1.
int GetCircle(const CIRCLE& cc0, const CIRCLE& cc1, double r, CIRCLE& c0, CIRCLE& c1) {
    c0.r = c1.r = r;
    return CIRCLE(cc0.c, cc0.r + r).CrossPoint(CIRCLE(cc1.c, cc1.r + r), c0.c, c1.c);
}
