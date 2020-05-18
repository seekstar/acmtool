//#define MAX_NODE1 (MAXN1 * 3)
//#define MAX_NODE2 (MAXN2 * 3)
struct SGT2 {
	int s[MAX_NODE1][MAX_NODE2], n1, n2;

	void Init(int _n1, int _n2) {
		n1 = _n1;
		n2 = _n2;
		for (int i = 1, n13 = n1 * 3, n23 = n2 * 3; i <= n13; ++i)
			memset(s[i], 0, n23 * sizeof(int));
	}
	void Add1(int rt, int l, int r, int x1, int x2, int v) {
		Add2(s[rt], 1, 1, n2, x2, v);
		if (l != r) {
			int mid = (l + r) >> 1;
			if (x1 <= mid) Add1(ls(rt), l, mid, x1, x2, v);
			else Add1(rs(rt), mid+1, r, x1, x2, v);
		}
	}
	void PushUp2(int s1[], int rt) {
		s1[rt] = s1[ls(rt)] + s1[rs(rt)];
	}
	void Add2(int s1[], int rt, int l, int r, int x, int v) {
		if (l == r) {
			s1[rt] += v;
		} else {
			int mid = (l + r) >> 1;
			if (x <= mid) Add2(s1, ls(rt), l, mid, x, v);
			else Add2(s1, rs(rt), mid+1, r, x, v);
			PushUp2(s1, rt);
		}
	}
	int Sum1(int rt, int l, int r, int L1, int R1, int L2, int R2) {
		if (L1 <= l && r <= R1) {
			return Sum2(s[rt], 1, 1, n2, L2, R2);
		} else {
			int ans = 0, mid = (l + r) >> 1;
			if (L1 <= mid) ans += Sum1(ls(rt), l, mid, L1, R1, L2, R2);
			if (mid < R1) ans += Sum1(rs(rt), mid+1, r, L1, R1, L2, R2);
			return ans;
		}
	}
	int Sum2(int s1[], int rt, int l, int r, int L, int R) {
		if (L <= l && r <= R) {
			return s1[rt];
		} else {
			int ans = 0, mid = (l + r) >> 1;
			if (L <= mid) ans += Sum2(s1, ls(rt), l, mid, L, R);
			if (mid < R) ans += Sum2(s1, rs(rt), mid+1, r, L, R);
			return ans;
		}
	}
};

