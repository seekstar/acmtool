struct PST_BASE {
    //0 is invalid
	const static int maxn = , max_node = ;
    int n, tot, roots[maxn], lson[max_node], rson[max_node], data[max_node];

    //Assume that maxv and n are given
    void Init(int _n) {
        //The content at the index 0 is never modified. So they are always 0
        n = _n;
        tot = 0;
        memset(roots, 0, (n + 1) * sizeof(roots[0]));
    }

    void Init(int a[], int _n, int maxv) {
        Init(_n);
        for (int i = 1; i <= n; ++i)
            Insert(roots[i-1], roots[i], 1, maxv, a[i], 1);
    }

    void Insert(int from, int &rt, int l, int r, int x, int num) {
        if (!rt) {
            rt = ++tot;
            lson[rt] = rson[rt] = data[rt] = 0;
        }
        data[rt] = data[from] + num;
        if (l < r) {
            int mid = (l + r) >> 1;
            if (x <= mid) {
                Insert(lson[from], lson[rt], l, mid, x, num);
                rson[rt] = rson[from];
            } else {
                lson[rt] = lson[from];
                Insert(rson[from], rson[rt], mid+1, r, x, num);
            }
        }
    }
};

