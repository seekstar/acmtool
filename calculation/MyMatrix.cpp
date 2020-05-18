//simple
struct MATRIX {
    const static int maxr = , maxc = ;
    int row, col;
    int s[maxr][maxc];

    void clear() {
        for (int i = 0; i < row; ++i)
            for (int j = 0; j < col; ++j)
                s[i][j] = 0;
    }
    void one() {
        clear();
        for (int i = 0; i < row; ++i)
            s[i][i] = 1;
    }

	//O(n^3 log(n))
    //p may be not prime
    int det_laplacian() {
        int ans = 1;
        for (int i = 0; i < row && ans; ++i) {
            for (int k = i + 1; k < row; ++k) {
                while (s[k][i]) {
                    int d = s[i][i] / s[k][i];
                    for (int j = i; j < col; ++j) {
                        swap(s[i][j], s[k][j]);
                        s[k][j] = (s[k][j] - (LL)s[i][j] * d) % p;
                    }
                    ans = -ans;
                }
            }
            ans = (LL)ans * s[i][i] % p;
        }
        return Sub(ans, p);
    }

	//O(n^3)
    int det_laplacian() {
        int ans = 1;
        for (int i = 0; i < row && ans; ++i) {
            if (0 == s[i][i]) return 0;
            int invi = Inv(s[i][i], p);
            for (int k = i + 1; k < row; ++k) {
                if (0 == s[k][i]) continue;
                int d = (LL)s[k][i] * invi % p;
                for (int j = i; j < col; ++j) {
                    s[k][j] = (s[k][j] - (LL)s[i][j] * d) % p;
                }
            }
            ans = (LL)ans * s[i][i] % p;
        }
        return Sub(ans, p);
    }

	//O(n^3)
    int det() {
        int ans = 1;
        for (int i = 0; i < row && ans; ++i) {
            if (0 == s[i][i]) {
                int k = i + 1;
                for (; k < row && 0 == s[k][i]; ++k);
                if (k == row) return 0;
                ans = -ans;
                for (int j = i; j < col; ++j)
                    swap(s[i][j], s[k][j]);
            }
            int invi = Inv(Sub(s[i][i], p), p);
            for (int k = i + 1; k < row; ++k) {
                if (0 == s[k][i]) continue;
                int d = (LL)s[k][i] * invi % p;
                for (int j = i; j < col; ++j) {
                    s[k][j] = (s[k][j] - (LL)s[i][j] * d) % p;
                }
            }
            ans = (LL)ans * s[i][i] % p;
        }
        return Sub(ans, p);
    }

    bool UpperTriangularMatrix(MATRIX& rec){
        bool fail = false;
        rec.col = rec.row = row;
        rec.one();
        for(int i = 1; i <= row; ++i){
            int maxVal = s[i][i];
            int maxRow = i;
            for(int k = i+1; k <= row; ++k){
                if(maxVal < s[k][i]){
                    maxVal = s[k][i];
                    maxRow = k;
                }
            }
            if(0 == maxVal){
                fail = true;
                break;
            }
            for(int j = i; j <= col; ++j){
                swap(s[i][j], s[maxRow][j]);
            }
            for(int j = 1; j <= rec.col; ++j){
                swap(rec.s[i][j], rec.s[maxRow][j]);
            }
            int tmp = inv(s[i][i]);
            for(int k = i+1; k <= row; ++k){
                int mk = (LL)s[k][i] * tmp % p;
                for(int j = i; j <= col; ++j){
                    SubMod(s[k][j] -= (LL)mk * s[i][j] % p);
                }
                for(int j = 1; j <= rec.col; ++j){
                    SubMod(rec.s[k][j] -= (LL)mk * rec.s[i][j] % p);
                }
            }
        }
        return fail;
    }
    bool Inv_destroy(MATRIX& ans){
        bool fail = UpperTriangularMatrix(ans);
        if(!fail){
            for(int i = row; i; --i){
                if(0 == s[i][i]){
                    fail = true;
                    break;
                }
                int tmp = inv(s[i][i]);
                for(int j = 1; j <= ans.col; ++j){
                    ans.s[i][j] = (LL)ans.s[i][j] * tmp % p;
                }
                for(int k = i - 1; k; --k){
                    for(int j = 1; j <= col; ++j){
                        SubMod(ans.s[k][j] -= (LL)ans.s[i][j] * s[k][i] % p);
                    }
                }
            }
        }
        return fail;
    }
};

template <typename T>
MATRIX mpow(MATRIX base, T ex) {
    MATRIX ans{base.row, base.col};
    ans.one();
    for (; ex; ex >>= 1, base = base * base)
        if (ex & 1)
            ans = ans * base;
    return ans;
}




struct MATRIX {
    const static int maxr = MAXN, maxc = MAXN;
    int row, col;
    double s[maxr][maxc];

    void clear() {
        for (int i = 0; i < row; ++i)
            for (int j = 0; j < col; ++j)
                s[i][j] = 0;
    }
    double det() {
        double ans = 1;
        for (int i = 0; i < row; ++i) {
            double maxv = fabs(s[i][i]);
            int maxr = i;
            for (int k = i + 1; k < row; ++k) {
                if (maxv < fabs(s[k][i])) {
                    maxv = fabs(s[k][i]);
                    maxr = k;
                }
            }
            if (maxv < eps) return 0;
            for (int j = i; j < col; ++j)
                swap(s[i][j], s[maxr][j]);
            for (int k = i + 1; k < row; ++k) {
                double d = s[k][i] / s[i][i];
                for (int j = i; j < col; ++j)
                    s[k][j] -= d * s[i][j];
            }
            ans *= s[i][i];
        }
        return ans;
    }
};


template<typename ElemType>
istream& operator >> (istream& in, Matrix<ElemType>& mat)
{
    for(int i = 0; i < (int)mat.m.size(); i++)
        for(int j = 0; j < (int)mat.m[i].size(); j++)
            in >> mat.m[i][j];
    return in;
}

template<typename ElemType>
ostream& operator << (ostream& out, const Matrix<ElemType>& mat)
{
	for(int i = 0; i < (int)mat.m.size(); i++)
	{
		for(int j = 0; j < (int)mat.m[i].size(); j++)
			out << mat.m[i][j] << ' ';
		out << endl;
	}
	return out;
}
