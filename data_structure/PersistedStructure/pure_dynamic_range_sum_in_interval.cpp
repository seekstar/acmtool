//#define MAX_NODE_PERSISTED MAXN
//#define MAX_SEG_NODE (MAXM * LOG_MAXN * LOG_MAXN)
//Pure dynamic
//The number of values less or equal x in an interval
struct PersistedSegTree {
	//static int maxn = MAXN, max_node = MAXM * LOG_MAXN * LOG_MAXN;
	//0 is invalid
	int n, maxv, roots[maxn], lson[max_node], rson[max_node], data[max_node], tot;

	//Assume that maxv and n are given
    void Init(int _n, int _maxv) {
        //The content at the index 0 is never modified. So they are always 0
        tot = 0;
        maxv = _maxv;
        n = _n;
        memset(roots, 0, (n+1) * sizeof(roots[0]));
    }
	void Insert(int& rt, int l, int r, int x, int num) {
		if (!rt) {
			rt = ++tot;
			lson[rt] = rson[rt] = data[rt] = 0;
		}
		data[rt] += num;
		if (l != r) {
			int mid = (l+r) >> 1;
			if (x <= mid)
				Insert(lson[rt], l, mid, x, num);
			else 
				Insert(rson[rt], mid+1, r, x, num);
		}
	}
	void Insert(int i, int x, int num) {
		for (; i <= n; i += lowbit(i))
			Insert(roots[i], 1, maxv+1, x, num);
	}

	int LeftSum(int rt[]) {
		int ans = 0;
		for (int i = 1; i <= rt[0]; ++i)
			ans += data[lson[rt[i]]];
		return ans;
	}
	void UpdateRt(int L_rt[], int R_rt[], int next[]) {
		for (int i = 1; i <= L_rt[0]; ++i)
			L_rt[i] = next[L_rt[i]];
		for (int i = 1; i <= R_rt[0]; ++i) 
			R_rt[i] = next[R_rt[i]];
	}
	//The number of values that in the range [1, x) in (L, R]
	//x = maxv+1 for the whole range
	int PrefixSum(int L, int R, int x) {
		static int L_rt[maxn], R_rt[maxn];
		int ans = 0;

		L_rt[0] = R_rt[0] = 0;
		for (int i = L; i; i ^= lowbit(i))
			L_rt[++L_rt[0]] = roots[i];
		for (int i = R; i; i ^= lowbit(i))
			R_rt[++R_rt[0]] = roots[i];
		int l = 1, r = maxv + 1;
		while (l < r) {
			int mid = (l + r) >> 1;
			if (x <= mid) {
				r = mid;
				UpdateRt(L_rt, R_rt, lson);
			} else {
				ans += LeftSum(R_rt) - LeftSum(L_rt);
				l = mid + 1;
				UpdateRt(L_rt, R_rt, rson);
			}
		}
		return ans;
	}
};

