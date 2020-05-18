typedef double FUNC(double);
double Simpson(FUNC f, double l, double r) {
	return (f(l) + 4 * f((l+r)/2) + f(r)) * (r - l) / 6;
}
double Integrate(FUNC f, double l, double r, double eps, double pre) {
	double mid = (l+r) / 2;
	double L = Simpson(f, l, mid), R = Simpson(f, mid, r), delta = L + R - pre;
	return fabs(delta) <= 15*eps ? L + R + delta/15 :
		Integrate(f, l, mid, eps/2, L) + Integrate(f, mid, r, eps/2, R);	//If you TLE, then try not divide 2, i.e. "eps/2" -> "eps"
}
inline double Integrate(FUNC f, double l, double r, double eps) {
	return Integrate(f, l, r, eps, Simpson(f, l, r));
}





struct Func {
    bool type;  //0: line, 1: circle
    double l, r;
    double c, R;
    bool operator < (const Func& b) const {
        return l != b.l ? l < b.l : (r < b.r);
    }
    double y(double x) const {
        if (type) {
            return sqrt(sq(R) - sq(x - c));
        } else {
            return c + (R - c) / (r - l) * (x - l);
        }
    }
};
#define fsnow const Func fs[], const unordered_set<int>& now
double Simpson(fsnow, double l, double r) {
    auto f = [&](double x) {
        double y = numeric_limits<double>::min();
        for (int i : now) {
            y = max(y, fs[i].y(x));
        }
        return y;
    };
    return (f(l) + 4 * f((l+r)/2) + f(r)) * (r - l) / 6;
};
double Integrate(fsnow, double l, double r, double eps, double pre) {
    double mid = (l+r) / 2;
    double L = Simpson(fs, now, l, mid), R = Simpson(fs, now, mid, r), delta = L + R - pre;
    return fabs(delta) <= 15*eps ? L + R + delta/15 :
           Integrate(fs, now, l, mid, eps/2, L) + Integrate(fs, now, mid, r, eps/2, R);	//If you TLE, then try not divide 2, i.e. "eps/2" -> "eps"
}
double Integrate(fsnow, double l, double r, double eps) {
    return Integrate(fs, now, l, r, eps, Simpson(fs, now, l, r));
}
double Integrate(Func fs[], int n, double eps) {
    struct REC {
        double r;
        int i;
        bool operator < (const REC& b) const {
            return r > b.r;
        }
    };
    sort(fs, fs + n);
    unordered_set<int> now;
    priority_queue<REC> right;
    double l = fs[0].l, ans = 0;
    for (int i = 0; i < n; ++i) {
        while (!right.empty() && right.top().r < fs[i].l) {
            ans += Integrate(fs, now, l, right.top().r, eps);
            l = right.top().r;
            now.erase(right.top().i);
            right.pop();
        }
        ans += Integrate(fs, now, l, fs[i].l, eps);
        right.push(REC{fs[i].r, i});
        now.insert(i);
        l = fs[i].l;
    }
    while (!right.empty()) {
        ans += Integrate(fs, now, l, right.top().r, eps);
        l = right.top().r;
        now.erase(right.top().i);
        right.pop();
    }
    return ans;
}



#define csn const CIRCLE cs[], int n
double Simpson(csn, double l, double r) {
    auto f = [=](double x) {
        static Interval lr[MAXN];
        int tot = 0;
        for (int i = 0; i < n; ++i)
            if (cs[i].Cross(lr[tot], x))
                ++tot;
        return IntervalOr(lr, tot);
    };
    return (f(l) + 4 * f((l+r)/2) + f(r)) * (r - l) / 6;
}
double Integrate(csn, double l, double r, double eps, double pre) {
    double mid = (l+r) / 2;
    double L = Simpson(cs, n, l, mid), R = Simpson(cs, n, mid, r), delta = L + R - pre;
    return fabs(delta) <= 15*eps ? L + R + delta/15 :
           Integrate(cs, n, l, mid, eps/2, L) + Integrate(cs, n, mid, r, eps/2, R);	//If you TLE, then try not divide 2, i.e. "eps/2" -> "eps"
}
double AreaOr(csn, double xl, double xr, double eps) {
    return Integrate(cs, n, xl, xr, eps, Simpson(cs, n, xl, xr));
}
#undef csn

