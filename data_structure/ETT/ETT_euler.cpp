struct ETT {
	int c[2 * MAXN][2], fa[2 * MAXN];
	int ori[MAXN * 2];
	// node[v][u] is the occurrence of v after u.
	// Corresponds to the directed edge from u to v.
	// If u is the parent of v, then it is the first occurrence of v.
	// i.e., if u is the parent of v, then uv is the first occurrence of v,
	// vu is the last occurrence of v.
	unordered_map<int, int> node[MAXN];
	stack<int> free_list;
	int tot;

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
		(void)x;
	}
	// pushup(x) later
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
		while (fa[x] != to) {
			int y = fa[x];
			if (fa[y] != to)
				__rotate_up(side(x) == side(y) ? y : x);
			__rotate_up(x);
		}
		pushup(x);
	}

	int new_node() {
		int x;
		if (!free_list.empty()) {
			x = free_list.top();
			free_list.pop();
		} else {
			x = ++tot;
		}
		return x;
	}
	void del_node(int x) {
		free_list.push(x);
	}

	int __find_min_or_max(int rt, bool mx) {
		while (c[rt][mx])
			rt = c[rt][mx];
		return rt;
	}
	int find_min_or_max(int rt, bool mx) {
		rt = __find_min_or_max(rt, mx);
		splay(rt);
		return rt;
	}

	void init(int n) {
		for (int i = 1; i <= n; ++i) {
			int x = new_node();
			ls(x) = rs(x) = fa[x] = 0;
			ori[x] = i;
			node[i][0] = x;
		}
	}
	void __concat(int x, int y) {
		node[ori[y]][ori[x]] = y;
		rs(x) = y;
		fa[y] = x;
	}
	void concat(int& x, int& y) {
		x = find_min_or_max(x, true);
		y = find_min_or_max(y, false);
		__concat(x, y);
	}
	void __append_node(int& x, int y, int u) {
		x = find_min_or_max(x, true);
		ls(y) = rs(y) = 0;
		ori[y] = u;
		__concat(x, y);
	}
	inline void append_node(int& x, int u) {
		__append_node(x, new_node(), u);
	}
	// aAuBa, a is the original root
	// Return the splay root(Not the tree root)
	int make_root(int u) {
		int x = node[u].begin()->second; // Any occurrence
		splay(x);
		int y = __find_min_or_max(x, false);
		if (ori[y] == u)
			return x; // Already root
		fa[ls(x)] = 0;
		ls(x) = 0;
		node[u][0] = x;
		// y: aA, x: uBa
		splay(y);
		node[ori[y]].erase(0);
		int tmp = y;
		y = rs(y);
		// y: A
		if (y) {
			fa[y] = 0;
			concat(x, y);
		}
		// x: uBaA
		__append_node(x, tmp, u);
		// x: uBaAu
		return x;
	}
	void link(int u, int v) {
		int x = node[u].begin()->second; // Any occurrence
		int y = make_root(v);
		append_node(y, u);
		splay(x);
		int x2 = rs(x);
		y = find_min_or_max(y, false);
		node[ori[y]].erase(0);
		__concat(x, y);
		if (x2) {
			fa[x2] = 0;
			concat(x, x2);
		}
	}
	void cut(int u, int v) {
		make_root(u); // To make sure that u is the father of v
		int uv = node[v][u];
		node[v].erase(u);
		node[v][0] = uv;
		auto vu = node[u][v];
		node[u].erase(v);
		splay(vu);
		splay(uv, vu);
		int x = ls(uv);
		fa[x] = 0;
		ls(uv) = 0;
		fa[uv] = 0;
		// ls(vu) = 0;
		int y = rs(vu);
		if (y) {
			fa[y] = 0;
			// rs(vu) = 0;
			concat(x, y);
		}
		del_node(vu);
	}
	bool in_the_same_splay(int u, int v) {
		if (u == v)
			return true;
		int x = node[u].begin()->second;
		splay(x);
		int y = node[v].begin()->second;
		splay(y);
		return fa[x] == y || fa[fa[x]] == y;
	}
};