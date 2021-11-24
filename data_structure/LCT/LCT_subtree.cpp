struct LCT {
	int c[MAXN][2], fa[MAXN], sta[MAXN];
	bool r[MAXN];
	// subtree_size2 is the sum of the sizes of non-preferred children's subtrees
	int subtree_size[MAXN], subtree_size2[MAXN];

	inline int& ls(int rt) {
		return c[rt][0];
	}
	inline int& rs(int rt) {
		return c[rt][1];
	}
	inline bool not_splay_rt(int x) {
		return ls(fa[x]) == x || rs(fa[x]) == x;
	}
	inline int side(int x) {
		return x == rs(fa[x]);
	}
	void Init(int n) {
		// Initially every node is a tree by itself.
		// memset all to 0.
		for (int i = 1; i <= n; ++i) {
			subtree_size[i] = 1;
		}
	}
	inline void pushr(int x) {
		swap(ls(x), rs(x));
		r[x] ^= 1;
	}
	inline void pushdown(int x) {
		if (r[x]) {
			if (ls(x))
				pushr(ls(x));
			if (rs(x))
				pushr(rs(x));
			r[x] = false;
		}
	}
	inline void pushup(int x) {
		subtree_size[x] = subtree_size[ls(x)] + subtree_size[rs(x)] + 1 + subtree_size2[x];
	}
	// s[x] is not updated
	void __rotate_up(int x) {
		int y = fa[x], z = fa[y], side_x = side(x), w = c[x][side_x ^ 1];
		fa[x] = z;
		if (not_splay_rt(y))
			c[z][side(y)] = x;
		if (w)
			fa[w] = y;
		c[y][side_x] = w;
		fa[y] = x;
		c[x][side_x ^ 1] = y;
		pushup(y);
	}
	// inline void rotate_up(int x) {
	// 	__rotate_up(x);
	// 	pushup(x);
	// }
	// s[x] is not updated
	void __splay(int x) {
		int y = x, top = 0;
		while(1) {
			sta[++top] = y;
			if (!not_splay_rt(y))
				break;
			y = fa[y];
		}
		int to = fa[y];
		while (top)
			pushdown(sta[top--]);
		while (fa[x] != to) {
			int y = fa[x];
			if (fa[y] != to)
				__rotate_up(side(x) == side(y) ? y : x);
			__rotate_up(x);
		}
	}
	inline void splay(int x) {
		__splay(x);
		pushup(x);
	}
	void access(int x) {
		int ori_x = x;
		for (int w = 0; x; w = x, x = fa[x]) {
			__splay(x);
			subtree_size2[x] += subtree_size[rs(x)];
			subtree_size2[x] -= subtree_size[w];
			rs(x) = w;
			pushup(x);
		}
		splay(ori_x);
	}
	int find_root(int x) {
		access(x);
		for (; ls(x); x = ls(x))
			pushdown(x);
		splay(x);
		return x;
	}
	inline void make_root(int x) {
		access(x);
		pushr(x);
	}
	void __link(int x, int y) {
		// If simply fa[x] = y, the complexity might be wrong.
		access(y);
		pushdown(x);
		fa[y] = x;
		ls(x) = y;
		pushup(x); // Might be unnecessary
	}
	inline void link_new(int x, int y) {
		make_root(x);
		__link(x, y);
	}
	inline void link(int x, int y) {
		make_root(x);
		if (find_root(y) == x)
			return;
		__link(x, y);
	}
	// cut(x, parent(x))
	// inline void cut(int x) {
	// 	access(x);
	// 	if (ls(x) == 0)
	// 		return;	// x has no parent
	// 	fa[ls(x)] = 0;
	// 	ls(x) = 0;
	// }
	inline void split(int x, int y) {
		make_root(x);
		access(y);
	}
	void cut_existing(int x, int y) {
		split(x, y);
		fa[x] = ls(y) = 0;
		pushup(y); // Might be unnecessary
	}
	void cut(int x, int y) {
		split(x, y);
		if (ls(y) != x || rs(x) != 0)
			return;	// No such edge (x, y)
		fa[x] = ls(y) = 0;
		pushup(y); // Might be unnecessary
	}
	inline unsigned int tree_size(int x) {
		access(x);
		return subtree_size[x];
	}
};
