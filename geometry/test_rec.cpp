const double eps = 1e-8;
const double pi = acos(-1.0);
int sgn(double x) {
    return fabs(x) < eps ? 0 : (x < 0 ? -1 : 1);
}

struct VEC {
	double rad(const VEC& b) const {
        return fabs(rad_di(b));
        //return asin(fabs(*this ^ b) / (len() * b.len()));
    }

	VEC rotright() const {
        return VEC{y, -x};
    }
    VEC rot(double a) const {
        double c = cos(a), s = sin(a);
        return VEC{x * c - y * s, x * s + y * c};
    }

	//Independent
    //0 <= angle < pi
    double angle() const {
        double ans = atan2(y, x);
        if (sgn(ans) < 0) ans += pi;
        else if (sgn(ans - pi) == 0) ans -= pi;
        return ans;
    }

	bool ToRightTest(const VEC& b) const {
        return sgn(*this ^ b) < 0;
    }
};


struct LINE {
    //ax + by + c = 0
    LINE(double a, double b, double c) : v(b, -a) {
        s = fabs(a) > fabs(b) ? VEC(-c / a, 0) : VEC(0, -c / b);
    }

	//0: parallel
    //1: coincide
    //2: intersect
    int relation(const LINE& b) const {
        if (v.parallel(b.v))
            return b.relation(s) == 0;
        return 2;
    }
	
	VEC symmetry(const VEC& p) const {
        VEC p0 = projection(p);
        return p0 * 2 - p;
    }
};

////////////////////////////////////////////tested
struct SEG : LINE {
    VEC e;

    SEG() {}

    SEG(const VEC &_s, const VEC &_e) : e(_e), LINE(_s, _e - _s) {}

    bool exclusive_between(const VEC& p) const {
        return sgn((p - s) * (p - e)) < 0;
    }
	
	bool between(const VEC& p) const {
        return (p - s) * (p - e) <= 0;
    }
    bool OnSeg(const VEC& p) const {
        return ((p - s) ^ v) == 0 && between(p);
    }
};

struct CIRCLE {
	double CrossArea(const CIRCLE& b) const {
        int rel = relation(b);
        if (rel >= 4) return 0;
        if (rel <= 2) return min(area(), b.area());
        double d = c.dist(b.c), hf = (r + b.r + d) / 2.0, S = sqrt(hf * (hf - r) * (hf - b.r) * (hf - d));
        double a1 = acos((sq(r) + sq(d) - sq(b.r)) / (2.0 * r * d));
        double a2 = acos((sq(b.r) + sq(d) - sq(r)) / (2.0 * b.r * d));
        return a1 + a2 - S;
    }

	
    bool operator == (const CIRCLE& b) const {
        return c == b.c && sgn(r - b.r) == 0;
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

