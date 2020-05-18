struct LINE {
    VEC s, v;
	void set(const VEC& _s, double a) {
        s = _s;
        v = {cos(a), sin(a)};
    }
	//ax + by + c = 0
	void set(double a, double b, double c) {
        v = {b, -a};
        s = fabs(a) > fabs(b) ? VEC{-c / a, 0} : VEC{0, -c / b};
    }

    //-1: left
    //0: on it
    //1: right
    int relation(const VEC& p) const {
        return sgn((p - s) ^ v);
    }
    //0: parallel
    //1: coincide
    //2: intersect
    int relation(const LINE& b) const {
        if (v.relation(b.v) == 0)
            return b.relation(s) == 0;
        return 2;
    }

    //Assume that they intersect
    VEC CrossPoint(const LINE& b) const {
        double t = ((b.s - s) ^ b.v) / (v ^ b.v);
        return s + v * t;
    }

    //left is plus
    double dist_di(const VEC& p) const {
        return (v ^ (p - s)) / v.len();
    }
	double dist(const VEC& p) const {
        return fabs(dist_di(p));
    }

    VEC projection(const VEC& p) const {
        VEC v1 = v.norm();
        return v1 * ((p - s) * v1) + s;
    }
    VEC symmetry(const VEC& p) const {
        VEC p0 = projection(p);
        return p0 * 2 - p;
    }

    void SetAngularBisector(const VEC& a, const VEC& b, const VEC& c) {
        set(a, (atan2(b.y - a.y, b.x - a.x) + atan2(c.y - a.y, c.x - a.x)) / 2);
    }
    
    LINE operator - () const {
        return LINE{s, -v};
    }

};
