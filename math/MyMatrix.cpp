	MATRIX& operator += (const MATRIX& b) {
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                AddMod(s[i][j] += b.s[i][j], p);
            }
        }
        return *this;
    }

    MATRIX operator * (const MATRIX& rhs) const {
        MATRIX ans{row, rhs.col};
        ans.clear();
        for (int i = 0; i < row; ++i)
            for (int j = 0; j < rhs.col; ++j)
                for (int k = 0; k < col; ++k)
                    ans.s[i][j] = (ans.s[i][j] + (LL)s[i][k] * rhs.s[k][j]) % p;
        return ans;
    }
    void input() {
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                scanf("%d", s[i] + j);
                s[i][j] %= p;
            }
        }
    }
    void print() const {
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                printf("%d%c", s[i][j], j == col - 1 ? '\n' : ' ');
            }
        }
    }
