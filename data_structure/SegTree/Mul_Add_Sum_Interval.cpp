//Multiple intervally, add intervally, get the sum of an interval
//#define MAX_NODE_SEGTREE (MAXN * 4)
template<typename ValType>
struct SegTree
{
    ValType val[MAX_NODE_SEGTREE];
    //The lazy tags are for the children. The root itself is up to date.
    ValType lazyMul[MAX_NODE_SEGTREE];  //multiple first, then add
    ValType lazyAdd[MAX_NODE_SEGTREE];

    inline int ls(int rt)
    {
        return rt << 1;
    }
    inline int rs(int rt)
    {
        return rt << 1 | 1;
    }
    void PushUp(int rt)
    {
        val[rt] = (val[ls(rt)] + val[rs(rt)]) % p;
    }
    void Build(int rt, int l, int r, int arr[])
    {
        if (l == r) {
            val[rt] = arr[l];
        } else {
            int mid = (l + r) >> 1;
            Build(ls(rt), l, mid, arr);
            Build(rs(rt), mid+1, r, arr);
            PushUp(rt);
        }
        lazyAdd[rt] = 0;
        lazyMul[rt] = 1;
    }
    void PushDown(int rt, int l, int mid, int r)
    {
        if (lazyMul[rt] != 1) {
            (lazyMul[ls(rt)] *= lazyMul[rt]) %= p;
            (lazyAdd[ls(rt)] *= lazyMul[rt]) %= p;
            (lazyMul[rs(rt)] *= lazyMul[rt]) %= p;
            (lazyAdd[rs(rt)] *= lazyMul[rt]) %= p;
            (val[ls(rt)] *= lazyMul[rt]) %= p;
            (val[rs(rt)] *= lazyMul[rt]) %= p;
            lazyMul[rt] = 1;
        }
        if (lazyAdd[rt]) {
            (lazyAdd[ls(rt)] += lazyAdd[rt]) %= p;
            (lazyAdd[rs(rt)] += lazyAdd[rt]) %= p;
            (val[ls(rt)] += lazyAdd[rt] * (mid - l + 1)) %= p;
            (val[rs(rt)] += lazyAdd[rt] * (r - mid)) %= p;
            lazyAdd[rt] = 0;
        }
    }
    void Add(int rt, int l, int r, int L, int R, ValType v)
    {
        if (L <= l && r <= R) {
            (val[rt] += (r - l + 1) * v) %= p;
            (lazyAdd[rt] += v) %= p;
        } else {
            int mid = (l + r) >> 1;
            PushDown(rt, l, mid, r);
            if (L <= mid) Add(ls(rt), l, mid, L, R, v);
            if (R > mid) Add(rs(rt), mid+1, r, L, R, v);
            PushUp(rt);
        }
    }
    void Mul(int rt, int l, int r, int L, int R, ValType v)
    {
        if (L <= l && r <= R) {
			(val[rt] *= v) %= p;
            (lazyMul[rt] *= v) %= p;
            (lazyAdd[rt] *= v) %= p;
        } else {
            int mid = (l + r) >> 1;
            PushDown(rt, l, mid, r);
            if (L <= mid) Mul(ls(rt), l, mid, L, R, v);
            if (R > mid) Mul(rs(rt), mid+1, r, L, R, v);
            PushUp(rt);
        }
    }
	//[L, R] mustn't be empty set!!!!
    ValType Sum(int rt, int l, int r, int L, int R)
    {
    	ValType ans = 0;
    	if (L <= l && r <= R) {
			ans = val[rt];
    	} else {
			int mid = (l + r) >> 1;
			PushDown(rt, l, mid, r);
			if (L <= mid) ans += Sum(ls(rt), l, mid, L, R);
			if (R > mid) (ans += Sum(rs(rt), mid+1, r, L, R)) %= p;
    	}
    	return ans;
    }
};
