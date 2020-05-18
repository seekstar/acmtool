//Heavy light decompostion
//path add, subtree add, path sum, subtree sum
struct HLD {
	SegTree<int> sgt;
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
	//t is the top of the current list
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
	int SumInPath(int x, int y) {
		int ans = 0;
		while (top[x] != top[y]) {
			if (depth[top[x]] < depth[top[y]])
				swap(x, y);
			AddMod(ans += sgt.Sum(1, 1, n, id[top[x]], id[x]), p);
			x = fa[top[x]];
		}
		if (depth[x] > depth[y])
			swap(x, y);
		AddMod(ans += sgt.Sum(1, 1, n, id[x], id[y]), p);
		return ans;
	}
	void AddInPath(int x, int y, int v) {
		v %= p;
		while (top[x] != top[y]) {
			if (depth[top[x]] < depth[top[y]])
				swap(x, y);
			sgt.Add(1, 1, n, id[top[x]], id[x], v);
			x = fa[top[x]];
		}
		if (depth[x] > depth[y])
			swap(x, y);
		sgt.Add(1, 1, n, id[x], id[y], v);
	}
	int SumSubTree(int x) {
		return sgt.Sum(1, 1, n, id[x], id[x] + siz[x] - 1);
	}
	void AddSubTree(int x, int v) {
		sgt.Add(1, 1, n, id[x], id[x] + siz[x] - 1, v);
	}
};

