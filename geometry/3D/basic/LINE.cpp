struct LINE {
    VEC s, v;
    double dist(const VEC& p) const {
        return (v ^ (p - s)).len() / v.len();
    }
    VEC projection(const VEC& p) const {
        VEC v1 = v.norm();
        return v1 * ((p - s) * v1) + s;
    }
};
