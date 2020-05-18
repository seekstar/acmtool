//#define MAX_NODE1 (MAXN << 2)
template<typename T>
struct LAZY {
	T v;
	int l, r;
};
template<typename T>
struct SGT2 {
	SGT<T> s[MAX_NODE1];
	int n2;
	LAZY<T> lazy[MAX_NODE1];

	void Init(int n1, int _n2) {
		n2 = _n2;
		memset(lazy, 0, ((n1 << 2)+1) * sizeof(int));
		for (int i = 0; i <= (n1 << 2); ++i)
			s[i].Init(n2);
	}
	void Init(int n1, int _n2, int a[][MAXM]) {
		n2 = _n2;
		Build(1, 1, n1, a);
	}
	void Build(int rt, int l, int r, int a[][MAXM]) {
		if (l == r) {
			s[rt].Build(1, 1, n2, a[l]);
		} else {
			int mid = (l + r) >> 1;
			Build(ls(rt), l, mid, a);
			Build(rs(rt), mid+1, r, a);
			for (int i = 1; i <= (n2 << 2); ++i)
				s[rt].sum[i] = s[ls(rt)].sum[i] + s[rs(rt)].sum[i];
		}
		lazy[rt] = LAZY<T>{0, 0, 0};
	}
	void PushDown(int rt, int l, int mid, int r) {
		T& v = lazy[rt].v, L = lazy[rt].l, R = lazy[rt].r;
		if (v) {
			lazy[ls(rt)].v += v;
			lazy[rs(rt)].v += v;
			s[ls(rt)].Add(1, 1, n2, L, R, v * (mid - l + 1));
			s[rs(rt)].Add(1, 1, n2, L, R, v * (r - mid));
			v = 0;
		}
	}
	//return the width that is modified
	int Add(int rt, int l, int r, int L1, int R1, int L2, int R2, int v) {
		int cnt = 0;
		if (L1 <= l && r <= R1) {
			cnt = r - l + 1;
			PushDown(rt, l, (l + r) >> 1, r);
			lazy[rt] = LAZY<T>{v, L2, R2};
		} else {
			int mid = (l + r) >> 1;
			PushDown(rt, l, mid, r);
			if (L1 <= mid) cnt = Add(ls(rt), l, mid, L1, R1, L2, R2, v);
			if (mid < R1) cnt += Add(rs(rt), mid+1, r, L1, R1, L2, R2, v);
		}
		s[rt].Add(1, 1, n2, L2, R2, v * cnt);
		return cnt;
	}
	
	T Sum(int rt, int l, int r, int L1, int R1, int L2, int R2) {
		if (L1 <= l && r <= R1) {
			return s[rt].Sum(1, 1, n2, L2, R2);
		} else {
			T ans = 0;
			int mid = (l + r) >> 1;
			PushDown(rt, l, mid, r);
			if (L1 <= mid) ans = Sum(ls(rt), l, mid, L1, R1, L2, R2);
			if (mid < R1) ans += Sum(rs(rt), mid+1, r, L1, R1, L2, R2);
			return ans;
		}
	}
};

