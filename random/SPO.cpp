template <typename T1, typename T2>
double Dist(const T1& lhs, const T2& rhs) {
    return sqrt(sq(lhs.x - rhs.x) + sq(lhs.y - rhs.y));
}


struct V {
    double x, y;
} ps[MAXN];
int num;



//minimize
const double minx = 0, miny = 0;
const double maxx = 1e4, maxy = 1e4;
default_random_engine e(time(NULL));
struct PSO {
    const static int maxpa = 21, maxit = 50;
    constexpr static double w = 0.4, c1 = 2, c2 = 2;
    double mvx, mvy;
    uniform_real_distribution<double> rx, ry, rvx, rvy, rc1, rc2;

    struct PARTICLE {
        double x, y, f;
        void set() {
            f = 0;
            for (int i = 0; i < num; ++i)
                f += Dist(*this, ps[i]);
        }
    } p[maxpa], pb[maxpa], gb;   //particle, particle best, global best
    V v[maxpa];

    PSO() : mvx(0.3 * (maxx - minx)), mvy(0.3 * (maxy - miny)), rx(minx, maxx), ry(miny, maxy), rvx(0, mvx), rvy(0, mvy), rc1(0, c1), rc2(0, c2) {
        gb.f = numeric_limits<double>::max();
        for (int i = 0; i < maxpa; ++i) {
            p[i].x = rx(e);
            p[i].y = ry(e);
            p[i].set();
            v[i].x = rvx(e);
            v[i].y = rvy(e);
            pb[i] = p[i];
            if (p[i].f < gb.f)
                gb = p[i];
        }
        for (int i = 0; i < maxit; ++i)
            Update();
    }

    void Update() {
        for (int i = 0; i < maxpa; ++i) {
            v[i].x = min(mvx, w * v[i].x + rc1(e) * (pb[i].x - p[i].x) + rc2(e) * (gb.x - p[i].x));
            v[i].y = min(mvy, w * v[i].y + rc1(e) * (pb[i].y - p[i].y) + rc2(e) * (gb.y - p[i].y));
            p[i].x += v[i].x;
            p[i].y += v[i].y;
            p[i].set();
            if (p[i].f < pb[i].f)
                pb[i] = p[i];
            if (p[i].f < gb.f)
                gb = p[i];
        }
    }
};







//maximize

#define MAXN 1011
int num;
struct V {
    double x, y;
} ps[MAXN];
const double minx = 0, miny = 0;
double maxx, maxy;
struct PSO {
    const static int maxpa = 21, maxit = 100;
    constexpr static double w1 = 0.4, w2 = 0.4, c1 = 2, c2 = 2; //w1 = 0.9, w2 = 0.4, or (0.3, 0.3) or (0.4, 0.4)
    double mvx, mvy, w;

    struct PARTICLE {
        double x, y, f;
        void set() {
            f = Fitness();
        }
        double Fitness() {
            if (x < 0 || x > maxx || y < 0 || y > maxy)
                return numeric_limits<double>::min();
            double ans = numeric_limits<double>::max();
            for (int i = 0; i < num; ++i)
                ans = min(ans, Dist(*this, ps[i]));
            return ans;
        }
    } p[maxpa], pb[maxpa], gb;   //particle, particle best, global best
    V v[maxpa];

    void Solve() {
        mvx = 0.3 * (maxx - minx);
        mvy = 0.3 * (maxy - miny);
        gb.f = numeric_limits<double>::min();
        for (int i = 0; i < maxpa; ++i) {
            p[i].x = maxx * rand() / RAND_MAX;
            p[i].y = maxy * rand() / RAND_MAX;
            p[i].set();
            v[i].x = mvx * rand() / RAND_MAX;
            v[i].y = mvy * rand() / RAND_MAX;
            pb[i] = p[i];
            if (p[i].f > gb.f)
                gb = p[i];
        }
        for (int i = 0; i < maxit; ++i) {
            w = w2 + w1 * (maxit - i) / maxit;
            Update();
        }
    }

    void Update() {
        for (int i = 0; i < maxpa; ++i) {
            v[i].x = min(mvx, w * v[i].x + c1 * rand() / RAND_MAX * (pb[i].x - p[i].x) + c2 * rand() / RAND_MAX * (gb.x - p[i].x));
            v[i].y = min(mvy, w * v[i].y + c1 * rand() / RAND_MAX * (pb[i].y - p[i].y) + c2 * rand() / RAND_MAX * (gb.y - p[i].y));
            p[i].x += v[i].x;
            p[i].y += v[i].y;
            p[i].set();
            if (p[i].f > pb[i].f)
                pb[i] = p[i];
            if (p[i].f > gb.f)
                gb = p[i];
        }
    }
};

