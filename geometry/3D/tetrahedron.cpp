double area2(const VEC& A, const VEC& B, const VEC& C) {
    return ((B - A) ^ (C - A)).len();
}
double volume6(const VEC& A, const VEC& B, const VEC& C, const VEC& D) {
    return fabs((B - A).MixedProd(C - A, D - A));
}
BALL InscribedBall(const VEC& A, const VEC& B, const VEC& C, const VEC& D) {
    double v6 = volume6(A, B, C, D);
    if (v6 < eps) return BALL{{0, 0, 0}, 0};
    double sa2 = area2(B, C, D);
    double sb2 = area2(A, C, D);
    double sc2 = area2(A, B, D);
    double sd2 = area2(A, B, C);
    double s2 = sa2 + sb2 + sc2 + sd2;
    return BALL{(A * sa2 + B * sb2 + C * sc2 + D * sd2) / s2,v6 / s2};
}
