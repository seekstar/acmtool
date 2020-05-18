struct SPLAY {
	int c[MAXN][2], fa[MAXN], siz[MAXN], tot, root, val[MAXN];
	bool lazy[MAXN];

#define ls(rt) c[rt][0]
#define rs(rt) c[rt][1]
	void Init(int vs[], int n) {
		root = tot = 0;
		Build(root, 0, 1, n, vs);
	}
	void PushUp(int rt) {
		siz[rt] = 1 + (ls(rt) ? siz[ls(rt)] : 0) + (rs(rt) ? siz[rs(rt)] : 0);
	}
	void Build(int& rt, int f, int l, int r, int vs[]) {
		if (l <= r) {
			int mid = (l + r) >> 1;
			rt = ++tot;
			siz[rt] = 1;
			fa[rt] = f;
			val[rt] = vs[mid];
			lazy[rt] = false;
			Build(ls(rt), rt, l, mid-1, vs);
			Build(rs(rt), rt, mid+1, r, vs);
			PushUp(rt);
		} else {
			rt = 0;
		}
	}
	inline bool Side(int rt) {
		return rt == rs(fa[rt]);
	}
	void PushDown(int rt) {
		if (lazy[rt]) {
			swap(ls(rt), rs(rt));
			if (ls(rt))
				lazy[ls(rt)] ^= 1;
			if (rs(rt))
				lazy[rs(rt)] ^= 1;
			lazy[rt] = false;
		}
	}
	void SetSon(int x, int f, bool side) {
		if (f) c[f][side] = x;
		if (x) fa[x] = f;
	}
	void RotateUp(int now) {
		int f = fa[now];
		bool side = Side(now);
		PushDown(f);
		PushDown(now);
		SetSon(c[now][!side], f, side);
		SetSon(now, fa[f], Side(f));
		SetSon(f, now, !side);
		PushUp(f);
		PushUp(now);
		if (!fa[now])
			root = now;
	}
	void Splay(int now, int to = 0) {
		if (!now) return;
		for (int f = fa[now]; f != to; f = fa[now]) {
			if (fa[f] != to)
				RotateUp(Side(now) == Side(f) ? f : now);
			RotateUp(now);
		}
	}

	int QueryKth(int k) {
		int rt = root;
		while (rt) {
			PushDown(rt);
			if (siz[ls(rt)] + 1 == k) {
				return rt;
			} else if (siz[ls(rt)] >= k) {
				rt = ls(rt);
			} else {
				k -= siz[ls(rt)] + 1;
				rt = rs(rt);
			}
		}
		return 0;
	}

	void Reverse(int L, int R) {
		int l = QueryKth(L), r = QueryKth(R+2);
		Splay(l);
		Splay(r, l);
		lazy[ls(r)] ^= 1;
	}
	void Traverse(int rt, int path[], int& len) {
		if (rt) {
			PushDown(rt);
			Traverse(ls(rt), path, len);
			path[len++] = val[rt];
			Traverse(rs(rt), path, len);
		}
	}
	void Traverse(int path[], int& len) {
		Traverse(root, path, len);
	}
};

