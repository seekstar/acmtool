inline int ls(int rt) {
	return rt << 1;
}
inline int rs(int rt) {
	return rt << 1 | 1;
}
#define MAX_NODE_SEGTREE (MAXM<<2)
template<typename T>
struct SGT {
	T sum[MAX_NODE_SEGTREE], lazy[MAX_NODE_SEGTREE];

	void Init(int n) {
		memset(sum, 0, (n<<2) * sizeof(T));
		memset(lazy, 0, (n<<2) * sizeof(T));
	}
	void PushUp(int rt) {
		sum[rt] = sum[ls(rt)] + sum[rs(rt)];
	}
	void Build(int rt, int l, int r, int arr[]) {
		if (l == r) {
			sum[rt] = arr[l];
		} else {
			int mid = (l+r) >> 1;
			Build(ls(rt), l, mid, arr);
			Build(rs(rt), mid+1, r, arr);
			PushUp(rt);
		}
		lazy[rt] = 0;
	}
	void PushDown(int rt, int l, int mid, int r) {
		if (lazy[rt]) {
			lazy[ls(rt)] += lazy[rt];
			lazy[rs(rt)] += lazy[rt];
			sum[ls(rt)] += lazy[rt] * (mid - l + 1);
			sum[rs(rt)] += lazy[rt] * (r - mid);
			lazy[rt] = 0;
		}
	}
	void Add(int rt, int l, int r, int L, int R, int v) {
		if (L <= l && r <= R) {
			lazy[rt] += v;
			sum[rt] += (T)(r - l + 1) * v;
		} else {
			int mid = (l + r) >> 1;
			PushDown(rt, l, mid, r);
			if (L <= mid)
				Add(ls(rt), l, mid, L, R, v);
			if (mid < R)
				Add(rs(rt), mid+1, r, L, R, v);
			PushUp(rt);
		}
	}
	T Sum(int rt, int l, int r, int L, int R) {
		if (L <= l && r <= R)
			return sum[rt];
		T ans = 0;
		int mid = (l + r) >> 1;
		PushDown(rt, l, mid, r);
		if (L <= mid)
			ans = Sum(ls(rt), l, mid, L, R);
		if (mid < R)
			ans += Sum(rs(rt), mid+1, r, L, R);
		return ans;
	}
};

