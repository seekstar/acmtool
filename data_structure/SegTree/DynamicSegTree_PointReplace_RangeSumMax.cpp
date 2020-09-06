#define MAXN_DSGT MAXTYPE
#define MAX_DSGT_NODE ((MAXN + MAXQ * 2) * LOG_MAXN)
struct DynamicSegTree {
	int roots[MAXN_DSGT], ls[MAX_DSGT_NODE], rs[MAX_DSGT_NODE], maxi[MAX_DSGT_NODE], sum[MAX_DSGT_NODE], tot;

	//n is the number of types
	void Init(int n) {
		tot = 0;
		memset(roots, 0, (n+1) * sizeof(int));
	}
	void PushUp(int rt) {
		sum[rt] = sum[ls[rt]] + sum[rs[rt]];
		maxi[rt] = max(maxi[ls[rt]], maxi[rs[rt]]);
	}
	void Update(int& rt, int l, int r, int x, int v) {
		if (!rt) {
			rt = ++tot;
			ls[rt] = rs[rt] = maxi[rt] = sum[rt] = 0;
		}
		if (l == r) {
			maxi[rt] = sum[rt] = v;
		} else {
			int mid = (l+r) >> 1;
			if (x <= mid)
				Update(ls[rt], l, mid, x, v);
			else
				Update(rs[rt], mid+1, r, x, v);
			PushUp(rt);
		}
	}
	int Sum(int rt, int l, int r, int L, int R) {
		if (!rt) return 0;
		if (L <= l && r <= R)
			return sum[rt];
		int ans = 0, mid = (l + r) >> 1;
		if (L <= mid) 
			ans = Sum(ls[rt], l, mid, L, R);
		if (mid < R) 
			ans += Sum(rs[rt], mid+1, r, L, R);
		return ans;
	}
	int Max(int rt, int l, int r, int L, int R) {
		if (!rt) return 0;
		if (L <= l && r <= R) {
			return maxi[rt];
		}
		int ans = 0, mid = (l + r) >> 1;
		if (L <= mid)
			ans = Max(ls[rt], l, mid, L, R);
		if (mid < R)
			ans = max(ans, Max(rs[rt], mid+1, r, L, R));
		return ans;
	}
};
