//Get the sum of k smallest values of a point(can be modified to support interval query).
//#define MAXN_PERSISTEDTREE MAXN
//#define MAX_SEG_NODE (MAXN * LOG_MAXN + MAXM * 2 * LOG_MAXN)
int maxv;
struct PersistedSegTree {
	int tot, roots[MAXN_PERSISTEDTREE], lson[MAX_SEG_NODE], rson[MAX_SEG_NODE], data[MAX_SEG_NODE];
	LL sum[MAX_SEG_NODE];

	void Init(int _maxv) {
		maxv = _maxv;
		tot = 0;
		roots[0] = Build(1, maxv);
	}
	int Build(int l, int r) {
		int rt = ++tot;
		data[rt] = 0;
		sum[rt] = 0;
		if (l < r) {
			int mid = (l + r) >> 1;
			lson[rt] = Build(l, mid);
			rson[rt] = Build(mid+1, r);
		}
		return rt;
	}
	int Update(int from, int x, int num, int add) {
		int rt = ++tot;
		int tmp = rt;

		data[rt] = data[from] + num;
		sum[rt] = sum[from] + add;
		int l = 1, r = maxv;
		while (l < r) {
			int mid = (l + r) >> 1;
			if (x <= mid) {
				rson[rt] = rson[from];
				from = lson[from];
				r = mid;
				rt = lson[rt] = ++tot;
			} else {
				lson[rt] = lson[from];
				from = rson[from];
				l = mid + 1;
				rt = rson[rt] = ++tot;
			}
			data[rt] = data[from] + num;
			sum[rt] = sum[from] + add;
		}
		return tmp;
	}
	LL Query(int rt, int l, int r, int k) {
		if (l == r)
			return data[rt] ? k * sum[rt] / data[rt] : 0;
		int mid = (l + r) >> 1;
		int data_lc = data[lson[rt]];
		LL sum_lc = sum[lson[rt]];
		if (data_lc >= k)
			return Query(lson[rt], l, mid, k);
		else
			return sum_lc + Query(rson[rt], mid+1, r, k - data_lc);
	}
};


