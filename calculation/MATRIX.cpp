struct MATRIX {
    vector<vector<int> > s;

    MATRIX() {}
    MATRIX(size_t a, size_t b) {
        resize(a, b);
    }
    inline size_t row() const {
        return s.size();
    }
    inline size_t col() const {
        return s.at(0).size();
    }
    void resize(size_t a, size_t b) {
        s.resize(a);
        for (size_t i = 0; i < a; ++i)
            s[i].resize(b);
    }
    void clear() {
        for (auto& i : s)
            for (auto& j : i)
                j = 0;
    }

    MATRIX operator * (const MATRIX& b) const {
        MATRIX ans(row(), b.col());
        assert(col() == b.row());
        for (size_t i = 0; i < row(); ++i)
            for (size_t j = 0; j < b.col(); ++j)
                for (size_t k = 0; k < col(); ++k)
                    ans.s[i][j] = (ans.s[i][j] + (LL)s[i][k] * b.s[k][j]) % mod;
        return ans;
    }
    MATRIX& operator += (const MATRIX& b) {
        for (size_t i = 0; i < row(); ++i)
            for (size_t j = 0; j < col(); ++j)
                AddMod(s[i][j] += b.s[i][j], mod);
        return *this;
    }
    MATRIX operator + (const MATRIX& b) const {
        return MATRIX(*this) += b;
    }
};


struct MATRIX {
    vector<vector<double> > s;

    MATRIX() {}
    MATRIX(size_t a, size_t b) {
        resize(a, b);
    }
    inline size_t row() const {
        return s.size();
    }
    inline size_t col() const {
        return s.at(0).size();
    }
    void resize(size_t a, size_t b) {
        s.resize(a);
        for (size_t i = 0; i < a; ++i)
            s[i].resize(b);
    }
    void clear() {
        for (auto& i : s)
            for (auto& j : i)
                j = 0;
    }
    void swap_row(size_t i, size_t j, size_t k = 0) {
        for (; k < col(); ++k)
            swap(s[i][k], s[j][k]);
    }
    //s[i] -= s[j] * d
    void sub_row(size_t i, size_t j, double d, size_t k = 0) {
        for (; k < col(); ++k)
            s[i][k] -= d * s[j][k];
    }
    //O(n^3)
    void ToUpper(MATRIX& b) {
        for (size_t i = 0; i < row(); ++i) {
            double maxv = fabs(s[i][i]);
            size_t mr = i;
            for (size_t j = i + 1; j < row(); ++j) {
                if (maxv < fabs(s[j][i])) {
                    maxv = fabs(s[j][i]);
                    mr = j;
                }
            }
            swap_row(i, mr, i);
            b.swap_row(i, mr);
            if (maxv < eps) continue;
            for (size_t j = i + 1; j < row(); ++j) {
                double d = s[j][i] / s[i][i];
                sub_row(j, i, d, i);
                b.sub_row(j, i, d);
            }
        }
    }
};

//ax = b
//b is ans
void solve_destory(MATRIX& a, MATRIX& b) {
    a.ToUpper(b);
    for (int i = a.row() - 1; i >= 0; --i) {
        assert(fabs(a.s[i][i]) > eps);
        b.s[i][0] /= a.s[i][i];
        for (int j = 0; j < i; ++j) {
            b.s[j][0] -= b.s[i][0] * a.s[j][i];
        }
    }
}
