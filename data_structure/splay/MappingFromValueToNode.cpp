struct SPLAY {
	int c[MAX_NODE_SPLAY][2], fa[MAX_NODE_SPLAY], siz[MAX_NODE_SPLAY], tot, root;
	int val[MAX_NODE_SPLAY], node[MAX_NODE_SPLAY];	//node[i] is the position of the node whose value is i

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
			node[val[rt]] = rt;
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
	void SetSon(int x, int f, bool side) {
		if (f) c[f][side] = x;
		if (x) fa[x] = f;
	}
	void RotateUp(int now) {
		int f = fa[now];
		bool side = Side(now);
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
	int QueryValOfKth(int k) {
		return val[QueryKth(k)];
	}

	int QuerySmaller(int v) {
		Splay(node[v]);
		return siz[ls(root)];
	}

	int FindPreOrNext(int now, bool nex) const {
		if (!c[now][nex]) return 0;
		nex = !nex;
		for (now = c[now][!nex]; c[now][nex]; now = c[now][nex]);
		return now;
	}
	void Top(int v) {
		int now = node[v];
		Splay(now);
		if (rs(now)) {
			int nex = FindPreOrNext(now, true);
			Splay(nex, now);
			SetSon(ls(now), nex, 0);
			ls(now) = 0;
			PushUp(nex);
			PushUp(now);
		} else {
			swap(ls(now), rs(now));
			PushUp(now);
		}
	}
	void Bottom(int v) {
		int now = node[v];
		Splay(now);
		if (ls(now)) {
			int pre = FindPreOrNext(now, false);
			Splay(pre, now);
			SetSon(rs(now), pre, 1);
			rs(now) = 0;
			PushUp(pre);
			PushUp(now);
		} else {
			swap(ls(now), rs(now));
			PushUp(now);
		}
	}
	void SwapInfo(int rt1, int rt2) {
		swap(node[val[rt1]], node[val[rt2]]);
		swap(val[rt1], val[rt2]);
	}
	void SwapWith(int v, bool nex) {
		int now = node[v];
		Splay(now);
		int to = FindPreOrNext(now, nex);
		Splay(to, now);
		SwapInfo(now, to);
		PushUp(to);
		PushUp(now);
	}
};

