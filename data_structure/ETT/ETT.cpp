struct ETT {
	int c[2 * MAXN][2], fa[2 * MAXN], sta[2 * MAXN];
	int ori[MAXN * 2], first[MAXN], last[MAXN];
	int mark[2 * MAXN]; // mark[x] is 1 if first occurrence. -1 if last occurrence.
	int mark_sum[2 * MAXN];
	LL val[2 * MAXN], s[2 * MAXN], lazy_add[2 * MAXN];

	inline int& ls(int rt) {
		return c[rt][0];
	}
	inline int& rs(int rt) {
		return c[rt][1];
	}
	inline int side(int x) {
		return x == rs(fa[x]);
	}
	void pushup(int x) {
		s[x] = s[ls(x)] + s[rs(x)] + val[x];
		mark_sum[x] = mark_sum[ls(x)] + mark_sum[rs(x)] + mark[x];
	}
	void dfs(const Graph& g, int u, int& tot) {
		first[u] = ++tot;
		ori[tot] = u;
		for (int v : g.s[u])
			dfs(g, v, tot);
		last[u] = ++tot;
		ori[tot] = -u;
	}
	int build(int l, int r, LL a[]) {
		int mid = (l + r) / 2;
		if (l < mid) {
			ls(mid) = build(l, mid - 1, a);
			fa[ls(mid)] = mid;
		}
		if (mid < r) {
			rs(mid) = build(mid + 1, r, a);
			fa[rs(mid)] = mid;
		}
		val[mid] = ori[mid] > 0 ? a[ori[mid]] : -a[-ori[mid]];
		mark[mid] = ori[mid] > 0 ? 1 : -1;
		pushup(mid);
		return mid;
	}
	void init(const Graph& g, int rt, LL a[]) {
		int tot = 0;
		dfs(g, rt, tot);
		build(1, tot, a);
	}
	inline void push_add(int x, LL c) {
		lazy_add[x] += c;
		val[x] += c * mark[x];
		s[x] += c * mark_sum[x];
	}
	void pushdown(int x) {
		if (lazy_add[x] != 0) {
			if (ls(x))
				push_add(ls(x), lazy_add[x]);
			if (rs(x))
				push_add(rs(x), lazy_add[x]);
			lazy_add[x] = 0;
		}
	}
	// s[x] is not updated
	void __rotate_up(int x) {
		int y = fa[x], z = fa[y], side_x = side(x), w = c[x][side_x ^ 1];
		fa[x] = z;
		if (z)
			c[z][side(y)] = x;
		if (w)
			fa[w] = y;
		c[y][side_x] = w;
		fa[y] = x;
		c[x][side_x ^ 1] = y;
		pushup(y);
	}
	void splay(int x, int to = 0) {
		int y = x, top = 0;
		while(1) {
			sta[++top] = y;
			if (fa[y] == to)
				break;
			y = fa[y];
		}
		while (top)
			pushdown(sta[top--]);
		while (fa[x] != to) {
			int y = fa[x];
			if (fa[y] != to)
				__rotate_up(side(x) == side(y) ? y : x);
			__rotate_up(x);
		}
		pushup(x);
	}
	int __find_prev_or_next(int rt, bool nxt) const {
		assert(fa[rt] == 0);
		if (!c[rt][nxt])
			return 0;
		rt = c[rt][nxt];
		while (c[rt][!nxt])
			rt = c[rt][!nxt];
		return rt;
	}
	LL path_sum(int u) {
		int x = first[u];
		splay(x);
		return s[ls(x)] + val[x];
	}
	void change_fa(int u, int new_fa) {
		splay(first[u]);
		int fa_first = __find_prev_or_next(first[u], false);
		splay(last[u]);
		int fa_last = __find_prev_or_next(last[u], true);
		splay(fa_first);
		splay(fa_last, fa_first);
		int x = ls(fa_last);
		ls(fa_last) = 0;
		pushup(fa_last);
		pushup(fa_first);

		splay(first[new_fa]);
		int y = __find_prev_or_next(first[new_fa], true);
		splay(y, first[new_fa]);
		ls(y) = x;
		fa[x] = y;
		pushup(y);
		pushup(first[new_fa]);
	}
	void subtree_add(int u, LL c) {
		splay(first[u]);
		splay(last[u], first[u]);
		push_add(ls(last[u]), c);
		val[last[u]] += c * mark[last[u]];
		pushup(last[u]);
		val[first[u]] += c * mark[first[u]];
		pushup(first[u]);
	}
};
