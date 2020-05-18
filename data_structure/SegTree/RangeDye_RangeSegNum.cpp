#define MAX_NODE_SEGTREE (MAXN<<2)
struct ColSeg {
	int num, head, rear;
	//Don't satisfy the law of commutation
	ColSeg operator + (const ColSeg& rhs) const {
		if (0 == num)
			return rhs;
		else if (0 == rhs.num)
			return *this;
		ColSeg ans{num + rhs.num, head, rhs.rear};
		if (rear == rhs.head)
			--ans.num;
		return ans;
	}
	ColSeg MergeHeadHead(const ColSeg& rhs) const {
		if (0 == num)
			return rhs;
		else if (0 == rhs.num)
			return *this;
		ColSeg ans{num+rhs.num, rear, rhs.rear};
		if (head == rhs.head)
			--ans.num;
		return ans;
	}
	void Dye(int v) {
		num = 1;
		head = rear = v;
	}
};
struct SegTree {
	int lazy[MAX_NODE_SEGTREE];
	ColSeg segs[MAX_NODE_SEGTREE];
	
	inline int ls(int rt) {
		return rt << 1;
	}
	inline int rs(int rt) {
		return rt << 1 | 1;
	}
	void PushUp(int rt) {
		segs[rt] = segs[ls(rt)] + segs[rs(rt)];
	}
	void Build(int rt, int l, int r, int arr[], int ori[]) {
		if (l == r) {
			segs[rt].Dye(arr[ori[l]]);
		} else {
			int mid = (l + r) >> 1;
			Build(ls(rt), l, mid, arr, ori);
			Build(rs(rt), mid+1, r, arr, ori);
			PushUp(rt);
		}
		lazy[rt] = 0;
	}
	void PushDown(int rt) {
		if (lazy[rt]) {
			segs[ls(rt)].Dye(lazy[rt]);
			segs[rs(rt)].Dye(lazy[rt]);
			lazy[ls(rt)] = lazy[rs(rt)] = lazy[rt];
			lazy[rt] = 0;
		}
	}
	void Replace(int rt, int l, int r, int L, int R, int v) {
		if (L <= l && r <= R) {
			segs[rt].Dye(v);
			lazy[rt] = v;
		} else {
			int mid = (l + r) >> 1;
			PushDown(rt);
			if (L <= mid) Replace(ls(rt), l, mid, L, R, v);
			if (R > mid) Replace(rs(rt), mid+1, r, L, R, v);
			PushUp(rt);
		}
	}
	ColSeg Seg(int rt, int l, int r, int L, int R) {
		if (L <= l && r <= R) {
			return segs[rt];
		} else {
			ColSeg ans{0, 0, 0};
			int mid = (l + r) >> 1;
			PushDown(rt);
			if (L <= mid) ans = Seg(ls(rt), l, mid, L, R);
			if (mid < R) ans = ans + Seg(rs(rt), mid+1, r, L, R);
			return ans;
		}
	}
};

