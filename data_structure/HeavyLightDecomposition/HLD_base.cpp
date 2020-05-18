struct HLD_base {
	int n, tot, fa[MAXN], depth[MAXN], siz[MAXN], son[MAXN], id[MAXN], top[MAXN], ori[MAXN];

	void Init(const GRAPH& g, int rt) {
		n = g.s.size()-1;
		tot = 0;
		memset(son, 0, (n+1) * sizeof(int));
		dfs1(g, rt, 0, 1);
		dfs2(g, rt, rt);
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
};

