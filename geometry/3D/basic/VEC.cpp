template <typename T>
T sq(T x) {
    return x * x;
}

const double eps = 1e-12, pi = acos(-1.0);
int sgn(double x) {
    return fabs(x) < eps ? 0 : (x < 0 ? -1 : 1);
}
struct VEC {
    double x, y, z;

	VEC operator + (const VEC& b) const {
        return VEC{x + b.x, y + b.y, z + b.z};
    }
    VEC operator - (const VEC& b) const {
        return VEC{x - b.x, y - b.y, z - b.z};
    }

    double len2() const {
        return sq(x) + sq(y) + sq(z);
    }
    double len() const {
        return sqrt(len2());
    }

	double dist2(const VEC& b) const {
        return (*this - b).len2();
    }
    double dist(const VEC& b) const {
        return (*this - b).len();
    }

	VEC operator * (double b) const {
        return VEC{x * b, y * b, z * b};
    }
    VEC trunc(double l) const {
        double ori = len();
        if (!sgn(ori)) return *this;
        return *this * (l / ori);
    }

	VEC operator / (double b) const {
        return VEC{x / b, y / b, z / b};
    }
    VEC norm() const {
        return *this / len();
    }

    VEC operator ^ (const VEC& b) const {
        return VEC{y * b.z - b.y * z, b.x * z - x * b.z, x * b.y - b.x * y};
    }
    double operator * (const VEC& b) const {
        return x * b.x + y * b.y + z * b.z;
    }

    double rad(const VEC& b) const {
        return fabs(atan2((*this ^ b).len(), *this * b));
    }
    double rad_acos(const VEC& b) const {
        double L1 = len2(), L2 = b.len2();
        return acos((L1 + L2 - (*this - b).len2()) / (2 * sqrt(L1) * sqrt(L2)));
    }

	double MixedProd(const VEC& b, const VEC& c) const {
        return *this * (b ^ c);
    }

    void input() {
        scanf("%lf%lf%lf", &x, &y, &z);
    }
};

