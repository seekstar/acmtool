//Replace intervally. Query the value at a point.
struct NODE
{
	int val;	//-1 means the colors are not the same
	bool lazy;
}tree[MAXN * 8];
void PushUp(int rt)
{
	tree[rt].val = tree[rt << 1].val == tree[rt << 1 | 1].val ? tree[rt << 1].val : -1;
}
void Build(int rt, int l, int r, int arr[])
{
	if(l != r)
	{
		int mid = (l + r) / 2;
		Build(rt << 1, l, mid, arr);
		Build(rt << 1 | 1, mid + 1, r, arr);
		PushUp(rt);
	}
	else
	{
		tree[rt].val = arr[l];
	}
	tree[rt].lazy = 0;
}
void PushDown(int rt)
{
	if(tree[rt].lazy)
	{
		tree[rt << 1] = tree[rt << 1 | 1] = tree[rt];	//lazy is copied,too
		tree[rt].lazy = 0;
	}
}
void modify(int rt, int l, int r, int L, int R, int val)
{
	if(L <= l && r <= R)
	{
		tree[rt].val = val;
		tree[rt].lazy = 1;
	}
	else if(!(R < l || r < L))
	{
		PushDown(rt);
		int mid = (l + r) / 2;
		modify(rt << 1, l, mid, L, R, val);
		modify(rt << 1 | 1, mid + 1, r, L, R, val);
		PushUp(rt);
	}
}
int query(int rt, int l, int r, int x)
{
	if(tree[rt].val != -1 || !(l <= x && x <= r))
	{
		return tree[rt].val;
	}
	else
	{
		PushDown(rt);
		int mid = (l + r) / 2;
		return mid < x ? query(rt << 1 | 1, mid + 1, r, x) : query(rt << 1, l, mid, x);
	}
}
