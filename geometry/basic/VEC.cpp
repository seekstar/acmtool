template <typename T>
T sq(T x) {
    return x * x;
}

const double eps = 1e-8, pi = acos(-1.0);
int sgn(double x) {
    return x < -eps ? -1 : (x > eps ? 1 : 0);
}

struct VEC {
    double x, y;
    bool operator == (const VEC& b) const {
        return sgn(x - b.x) == 0 && sgn(y - b.y) == 0;
    }
	bool operator < (const VEC& b) const {
        return sgn(y - b.y) == 0 ? sgn(x - b.x) < 0 : y < b.y;
    }

    VEC operator - (const VEC& b) const {
        return VEC{x - b.x, y - b.y};
    }
    VEC operator + (const VEC& b) const {
        return VEC{x + b.x, y + b.y};
    }

    double len() const {
        return hypot(x, y);
    }
    double dist(const VEC& b) const {
        return (*this - b).len();
    }

	double len2() const {
        return sq(x) + sq(y);
    }
    double dist2(const VEC& b) const {
        return (*this - b).len2();
    }

	VEC operator * (double k) const {
        return VEC{x * k, y * k};
    }
	VEC trunc(double l) const {
        double ori = len();
        if (!sgn(ori)) return *this;
        return *this * (l / ori);
    }

    VEC operator / (double k) const {
        return VEC{x / k, y / k};
    }
	VEC norm() const {
        return *this / len();
    }

	double operator ^ (const VEC& b) const {
        return x * b.y - y * b.x;
    }
    double operator * (const VEC& b) const {
        return x * b.x + y * b.y;
    }
    // The angle between *this and b
    //anticlockwise is plus
    double rad_di(const VEC& b) const {
        return atan2(*this ^ b, *this * b);
    }
    double rad(const VEC& b) const {
        return fabs(rad_di(b));
        //return asin(fabs(*this ^ b) / (len() * b.len()));
    }

    VEC rotleft() const {
        return VEC{-y, x};
    }
    VEC rotright() const {
        return VEC{y, -x};
    }
    VEC rot(double a) const {
        double c = cos(a), s = sin(a);
        return VEC{x * c - y * s, x * s + y * c};
    }

	//Independent
    //0 <= slope < pi
    double slope() const {
        double ans = atan2(y, x);
        if (sgn(ans) < 0) ans += pi;
        else if (sgn(ans - pi) == 0) ans -= pi;
        return ans;
    }

    double cross(const VEC& p1, const VEC& p2) const {
        return (p1 - *this) ^ (p2 - *this);
    }

	//-1: left
	//0: parallel
	//1: right
	int relation(const VEC& b) const {
		return sgn(b ^ *this);
	}

	VEC operator - () const {
        return VEC{-x, -y};
    }
    bool SameDi(const VEC& b) const {
        return sgn(x) == sgn(b.x) && sgn(y) == sgn(b.y);
    }

	void input() {
        scanf("%lf%lf", &x, &y);
    }
};
