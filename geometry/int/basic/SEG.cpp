struct SEG : LINE {
    VEC e;
    SEG() {}
    SEG(const VEC& _s, const VEC& _e) : e(_e), LINE{_s, _e - _s} {}

    bool between(const VEC& p) const {
        return (p - s) * (p - e) <= 0;
    }
    bool OnSeg(const VEC& p) const {
        return ((p - s) ^ v) == 0 && between(p);
    }

	//0: Not cross
    //1: Just cross (unnorm cross 非规范相交)
    //2: Cross inner (norm cross 规范相交)
    int Cross(const SEG& b) const {
        int d1 = sgn(v ^ (b.s - s));
        int d2 = sgn(v ^ (b.e - s));
        int d3 = sgn(b.v ^ (s - b.s));
        int d4 = sgn(b.v ^ (e - b.s));
        if ((d1 ^ d2) == -2 && (d3 ^ d4) == -2) return 2;
        else return (d1 == 0 && between(b.s)) || (d2 == 0 && between(b.e)) ||
                    (d3 == 0 && b.between(s)) || (d4 == 0 && b.between(e));
    }
};
