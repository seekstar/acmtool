template <typename LINE>
bool OutOfConvex(const VEC& p, const LINE ls[], int n) {
    bool s[3];
    memset(s, 0, sizeof(s));
    for (int i = 0; i < n && !(s[0] && s[2]); ++i)
        s[ls[i].relation(p) + 1] = true;
    return s[0] && s[2];
}
