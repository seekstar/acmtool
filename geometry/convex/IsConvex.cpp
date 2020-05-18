bool IsConvex(const VEC ps[], int n) {
    static bool s[3];
    memset(s, 0, sizeof(s));
    for (int i = 0; i < n && !(s[0] && s[2]); ++i) {
        int i1 = Add(i + 1, n);
        int i2 = Add(i1 + 1, n);
        s[sgn((ps[i1] - ps[i]) ^ (ps[i2] - ps[i])) + 1] = true;
    }
    return !(s[0] && s[2]);
}
