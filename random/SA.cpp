struct INFO {
    double x, y, f;
    INFO() {}
    INFO(double _x, double _y) : x(_x), y(_y) {
        set();
    }
    void set() {
        f = 0;
        for (int i = 0; i < n; ++i) {
            f += Dist(*this, ps[i]);
        }
    }
};
//minimize
//t is step, no less than the radius of the area.
//The initial position is the mean of the points.
const double eps = 1e-8, delta = 0.98;
void SA(double t, INFO& gb) {
    INFO now = gb;
    while (t > eps) {
        INFO next(now.x + ((rand() << 1) - RAND_MAX) * t, now.y + ((rand() << 1) - RAND_MAX) * t);
        double dE = next.f - now.f;
        if (dE < 0 || exp(-dE / t) * RAND_MAX > rand())
            now = next;
        if (now.f < gb.f)
            gb = now;
        t *= delta;
    }
}


default_random_engine e(time(NULL));
uniform_real_distribution<double> rm1(-RAND_MAX, RAND_MAX), r1(0, 1);
//minimize
//t is step, no less than the radius of the area.
//The initial position is the center of the area.
const double eps = 1e-8, delta = 0.99;
void SA(double t, INFO& gb) {
    INFO now = gb;
    while (t > eps) {
        INFO next(now.x + t * rm1(e), now.y + t * rm1(e));
        double dE = next.f - now.f;
        if (dE < 0 || exp(-dE / t) > r1(e))
            now = next;
        if (now.f < gb.f)
            gb = now;
        t *= delta;
    }
}
