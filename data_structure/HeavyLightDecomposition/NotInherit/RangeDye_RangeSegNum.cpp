struct HLD {
	SegTree sgt;
	int n, tot, fa[MAXN], depth[MAXN], siz[MAXN], son[MAXN], id[MAXN], top[MAXN], ori[MAXN];
	void Init(const GRAPH& g, int rt, int arr[]) {
		n = g.s.size()-1;
		tot = 0;
		memset(son, 0, (n+1) * sizeof(int));
		dfs1(g, rt, 0, 1);
		dfs2(g, rt, rt);
		sgt.Build(1, 1, n, arr, ori);
	}
	void dfs1(const GRAPH& g, int s, int f, int d) {
		depth[s] = d;
		fa[s] = f;
		siz[s] = 1;
		for (int v : g.s[s]) {
			if (v == f) continue;
			dfs1(g, v, s, d+1);
			siz[s] += siz[v];
			if (siz[v] > siz[son[s]])
				son[s] = v;
		}
	}
	void dfs2(const GRAPH& g, int s, int t) {
		top[s] = t;
		id[s] = ++tot;
		ori[tot] = s;
		if (!son[s]) return;
		dfs2(g, son[s], t);
		for (int v : g.s[s])
			if (v != son[s] && v != fa[s])
				dfs2(g, v, v);
	}
	int SegNumInPath(int x, int y) {
		ColSeg ansx{0, 0, 0};
		ColSeg ansy{0, 0, 0};
		while (top[x] != top[y]) {
			if (depth[top[x]] < depth[top[y]]) {
				swap(ansx, ansy);
				swap(x, y);
			}
			ansx = sgt.Seg(1, 1, n, id[top[x]], id[x]) + ansx;
			x = fa[top[x]];
		}
		if (depth[x] > depth[y]) {
			swap(ansx, ansy);
			swap(x, y);
		}
		ansy = sgt.Seg(1, 1, n, id[x], id[y]) + ansy;
		return ansx.MergeHeadHead(ansy).num;
	}
	void DyePath(int x, int y, int v) {
		while (top[x] != top[y]) {
			if (depth[top[x]] < depth[top[y]])
				swap(x, y);
			sgt.Replace(1, 1, n, id[top[x]], id[x], v);
			x = fa[top[x]];
		}
		if (depth[x] > depth[y])
			swap(x, y);
		sgt.Replace(1, 1, n, id[x], id[y], v);
	}
};

