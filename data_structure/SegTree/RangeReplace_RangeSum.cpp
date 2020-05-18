#define MAX_NODE_SEGTREE (MAXN<<2)
//Range replace, range sum
template<typename T>
struct SegTree {
	T sum[MAX_NODE_SEGTREE];
	T lazy[MAX_NODE_SEGTREE];

	void Init(int n) {
		memset(lazy, -1, (n<<2) * sizeof(lazy[0]));
		memset(sum, 0, (n<<2) * sizeof(sum[0]));
	}
	inline int ls(int rt) {
		return rt << 1;
	}
	inline int rs(int rt) {
		return rt << 1 | 1;
	}
	void PushUp(int rt) {
		sum[rt] = sum[ls(rt)] + sum[rs(rt)];
	}
	void Build(int rt, int l, int r, T a[]) {
		if (l == r) {
			sum[rt] = a[l];
		} else {
			int mid = (l + r) >> 1;
			Build(ls(rt), l, mid, a);
			Build(rs(rt), mid+1, r, a);
			PushUp(rt);
		}
		lazy[rt] = -1;
	}
	void PushDown(int rt, int l, int mid, int r) {
		if (lazy[rt] >= 0) {
			lazy[ls(rt)] = lazy[rs(rt)] = lazy[rt];
			sum[ls(rt)] = (mid-l+1) * lazy[rt];
			sum[rs(rt)] = (r-mid) * lazy[rt];
			lazy[rt] = -1;
		}
	}
	void Replace(int rt, int l, int r, int L, int R, T v) {
		if (L <= l && r <= R) {
			lazy[rt] = v;
			sum[rt] = (r-l+1) * v;
		} else {
			int mid = (l + r) >> 1;
			PushDown(rt, l, mid, r);
			if (L <= mid) 
				Replace(ls(rt), l, mid, L, R, v);
			if (R > mid) 
				Replace(rs(rt), mid+1, r, L, R, v);
			PushUp(rt);
		}
	}
	T Sum(int rt, int l, int r, int L, int R) {
		if (L <= l && r <= R) {
			return sum[rt];
		}
		T ans = 0;
		int mid = (l + r) >> 1;
		PushDown(rt, l, mid, r);
		if (L <= mid) 
			ans = Sum(ls(rt), l, mid, L, R);
		if (R > mid) 
			ans += Sum(rs(rt), mid+1, r, L, R);
		return ans;
	}
};

