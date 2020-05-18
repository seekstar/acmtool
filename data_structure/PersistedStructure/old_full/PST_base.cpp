//#define MAX_SEG_NODE (MAXN * LOG_MAXN + MAXM * LOG_MAXN * LOG_MAXN)
struct PST_base {
	int tot, roots[MAXN_PST], lson[MAX_SEG_NODE], rson[MAX_SEG_NODE], data[MAX_SEG_NODE];

	inline void Init(int maxv) {
		tot = 0;
		roots[0] = Build(1, maxv);
	}
	void Init(int a[], int n, int maxv) {
		Init(maxv);
		for (int i = 1; i <= n; ++i)
			roots[i] = Insert(roots[i-1], 1, maxv, a[i], 1);
	}
	int Build(int l, int r) {
		int rt = ++tot;
		data[rt] = 0;
		if (l < r) {
			int mid = (l + r) >> 1;
			lson[rt] = Build(l, mid);
			rson[rt] = Build(mid+1, r);
		}
		return rt;
	}
	int Insert(int from, int l, int r, int x, int num) {
		int rt = ++tot;
		data[rt] = data[from] + num;
		if (l < r) {
			int mid = (l+r) >> 1;
			if (x <= mid) {
				lson[rt] = Insert(lson[from], l, mid, x, num);
				rson[rt] = rson[from];
			} else {
				lson[rt] = lson[from];
				rson[rt] = Insert(rson[from], mid+1, r, x, num);
			}
		}
		return rt;
	}
	/*int Insert(int from, int x, int num, int len)
    {
        int rt = ++tot;
        int tmp = rt;

        data[rt] = data[from] + num;
        int l = 1, r = len;
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
        }
        return tmp;
    }*/
};

