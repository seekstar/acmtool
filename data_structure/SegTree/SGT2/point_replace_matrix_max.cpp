template<typename T>
struct SGT2 {
	const static int max_node = MAXN1 << 2;
	SGT<T> s[max_node];
	int n2;

	void Init(int n1, int _n2) {
		n2 = _n2;
		for (int i = 0; i <= (n1<<2); ++i)
			s[i].Init(n2);
	}
	void Modify(int rt, int l, int r, int x1, int x2, int v) {
		s[rt].Modify(1, 1, n2, x2, v);
		if (l != r) {
			int mid = (l + r) >> 1;
			if (x1 <= mid) Modify(ls(rt), l, mid, x1, x2, v);
			else Modify(rs(rt), mid+1, r, x1, x2, v);
		}
	}
	int Max(int rt, int l, int r, int L1, int R1, int L2, int R2) {
		if (L1 <= l && r <= R1) {
			return s[rt].Max(1, 1, n2, L2, R2);
		} else {
			int ans = numeric_limits<T>::min(), mid = (l + r) >> 1;
			if (L1 <= mid) ans = Max(ls(rt), l, mid, L1, R1, L2, R2);
			if (mid < R1) ans = max(ans, Max(rs(rt), mid+1, r, L1, R1, L2, R2));
			return ans;
		}
	}
};
