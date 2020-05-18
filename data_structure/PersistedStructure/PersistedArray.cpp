struct Node
{
    int lc, rc, val;
} tree[MAXN << 5];
int len_tree = 0;

int roots[MAXN];

void Build(int& rt, int l, int r, int base[MAXN])
{
    rt = ++len_tree;
    if(l != r)
    {
        int mid = (l+r) >> 1;
        Build(tree[rt].lc, l, mid, base);
        Build(tree[rt].rc, mid+1, r, base);
    }
    else
    {
        tree[rt].val = base[l];
    }
}

void Update(int& rt, int from, int l, int r, int x, int val)
{
    rt = ++len_tree;
    if(l == r)
        tree[rt].val = val;
    else
    {
    	int mid = (l + r) >> 1;
        if(x <= mid)
        {
            Update(tree[rt].lc, tree[from].lc, l, mid, x, val);
            tree[rt].rc = tree[from].rc;
        }
        else
        {
            tree[rt].lc = tree[from].lc;
            Update(tree[rt].rc, tree[from].rc, mid+1, r, x, val);
        }
    }
}

int Query(int rt, int l, int r, int x)
{
    if(l == r)return tree[rt].val;
    int mid = (l + r) >> 1;
    if(x <= mid)return Query(tree[rt].lc, l, mid, x);
    else return Query(tree[rt].rc, mid+1, r, x);
}
