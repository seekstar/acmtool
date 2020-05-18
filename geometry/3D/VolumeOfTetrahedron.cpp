//input the length of the six edges
double VolumeOfTetrahedron(double p, double q, double r, double n, double m, double l) {
    p *= p;
    q *= q;
    r *= r;
    n *= n;
    m *= m;
    l *= l;
    double t1 = (p + q - n) / 2;
    double t2 = (p + r - m) / 2;
    double t3 = (q + r - l) / 2;
    double a1 = p * (q * r - t3 * t3);
    double a2 = t1 * (t2 * t3 - t1 * r);
    double a3 = t2 * (t1 * t3 - q * t2);
    return sqrt(a1 + a2 + a3) / 6.0;
}