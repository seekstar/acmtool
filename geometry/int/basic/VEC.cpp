template <typename T>
T sq(T x) {
    return x * x;
}

int sgn(LT x) {
    return x < 0 ? -1 : (x > 0 ? 1 : 0);
}
struct VEC {
    LT x, y;

    VEC operator + (const VEC& b) const {
        return VEC{x + b.x, y + b.y};
    }
    bool operator == (const VEC& b) const {
        return x == b.x && y == b.y;
    }
    bool operator < (const VEC& b) const {
        return y != b.y ? y < b.y : x < b.x;
    }

    VEC operator - (const VEC& b) const {
        return VEC{x - b.x, y - b.y};
    }

    LT len2() const {
        return sq(x) + sq(y);
    }
    LT dist2(const VEC& b) const {
        return (*this - b).len2();
    }

    //Might overflow
    LT operator * (const VEC& b) const {
        return x * b.x + y * b.y;
    }
    LT operator ^ (const VEC& b) const {
        return x * b.y - y * b.x;
    }

    bool ToLeftTest(const VEC& b) const {
        return (*this ^ b) > 0;
    }
    bool ToRightTest(const VEC& b) const {
        return (*this ^ b) < 0;
    }

	LT cross(const VEC& p1, const VEC& p2) const {
        return (p1 - *this) ^ (p2 - *this);
    }
};
