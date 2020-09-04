template<typename T>
struct SGT {
	//const static int max_node = MAXN << 2;
	T maxi[max_node];

	void Init(int n) {
		memset(maxi, 0xc0, (n<<2) * sizeof(T));
	}
	void PushUp(int rt) {
		maxi[rt] = max(maxi[ls(rt)], maxi[rs(rt)]);
	}
	void Modify(int rt, int l, int r, int x, int v) {
		if (l == r) {
			maxi[rt] = max(maxi[rt], v);
		} else {
			int mid = (l + r) >> 1;
			if (x <= mid) Modify(ls(rt), l, mid, x, v);
			else Modify(rs(rt), mid+1, r, x, v);
			PushUp(rt);
		}
	}
	T Max(int rt, int l, int r, int L, int R) {
		if (L <= l && r <= R) {
			return maxi[rt];
		} else {
			T ans = numeric_limits<T>::min();
			int mid = (l + r) >> 1;
			if (L <= mid) ans = Max(ls(rt), l, mid, L, R);
			if (mid < R) ans = max(ans, Max(rs(rt), mid+1, r, L, R));
			return ans;
		}
	}
};
