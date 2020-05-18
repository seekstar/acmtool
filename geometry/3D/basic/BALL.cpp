struct BALL {
    VEC c;
    double r;

    bool operator == (const BALL& b) const {
        return sgn((c - b.c).len()) == 0 && sgn(r - b.r) == 0;
    }

	//-1: inside
    //0: on
    //1: out
    int relation(const VEC& p) const {
        return sgn(p.dist(c) - r);
    }
	//-1: intersect
    //0: tangent
    //1: out
    int relation(const LINE& b) const {
        return sgn(b.dist(c) - r);
    }
    //1: inside
    //2: internally tangent
    //3: Cross
    //4: externally tangent
    //5: away from
    int relation(const BALL& b) const {
        double d = c.dist(b.c);
        int s = sgn(d - fabs(b.r - r));
        if (s <= 0) return s + 2;
        return sgn(d - (b.r + r)) + 4;
    }

    //-1: infinite
    int cross(CIRCLE3& ans, const BALL& b) const {
        int rel = relation(b);
        if (rel == 1 || rel == 5) return 0;
        if (*this == b) return -1;
        ans.v = (b.c - c).norm();
        //WA ???? poj 2177
        //double d2 = c.dist2(b.c);
        //double l = (sq(r) + d2 - sq(b.r)) / (2 * sqrt(d2)); //projection of r on d
        double d = c.dist(b.c);
        double l = (sq(r) + sq(d) - sq(b.r)) / (2 * d);
        ans.c = c + ans.v * l;
        ans.r = sqrt(sq(r) - sq(l));
        return 1;
    }

	void SetCircumscribed(const VEC& A, const VEC& B) {
        c = (A + B) / 2.0;
        r = (B - A).len() / 2.0;
    }
    //outer
    //Make sure that A, B, C are not collinear
    void SetCircumscribed(const VEC& A, VEC B, VEC C) {
        B = B - A;
        C = C - A;
        VEC s2di = B ^ C;
        if (s2di.len() < eps) return;
        VEC abv = s2di ^ B;
        VEC acv = C ^ s2di;
        VEC to = (abv * C.len2() + acv * B.len2()) / (2.0 * s2di.len2());
        c = A + to;
        r = to.len();
    }
    //Make sure that A, B, C, D are not in the same plane
    void SetCircumscribed(const VEC& A, const VEC& B, const VEC& C, VEC D) {
        SetCircumscribed(A, B, C);
        VEC v = ((C - A) ^ (B - A)).norm();
        D = D - c;
        double L = D * v, d2 = (v ^ D).len2();
        if (fabs(L) < eps) return;
        double k = (d2 + sq(L) - sq(r)) / (2 * L);
        c = c + v * k;
        r = sqrt(sq(k) + sq(r));
    }
};

