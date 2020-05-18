struct SPLAY {
	int c[MAXN][2], fa[MAXN], cnt[MAXN], tot, root, mini[MAXN];
	int val[MAXN];
	set<pair<int, int> > node;

#define ls(rt) c[rt][0]
#define rs(rt) c[rt][1]
	void Init(int n) {
		root = tot = 0;
		node.clear();
	}
	void PushUp(int rt) {
		mini[rt] = min(val[rt], min(ls(rt) ? mini[ls(rt)] : 0x3f3f3f3f, rs(rt) ? mini[rs(rt)] : 0x3f3f3f3f));
	}

	inline bool Side(int rt) {
		return rt == rs(fa[rt]);
	}
	inline void SetSon(int x, int f, bool side) {
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

	void Init(int rt, int v) {
		c[rt][0] = c[rt][1] = fa[rt] = 0;
		val[rt] = mini[rt] = v;
		node.insert(make_pair(v, rt));
	}
	void InsertBottom(int v) {
		int new_node = ++tot;
		Init(new_node, v);
		if (!root) {
			root = new_node;
			return;
		}
		int now = root;
		for (; rs(now); now = rs(now));
		Splay(now);
		SetSon(new_node, root, 1);
		PushUp(root);
	}

	int FindPreOrNext(int now, bool nex) const {
		if (!c[now][nex]) return 0;
		nex = !nex;
		for (now = c[now][!nex]; c[now][nex]; now = c[now][nex]);
		return now;
	}
	void DelRoot() {
		node.erase(make_pair(val[root], root));
		int now = FindPreOrNext(root, false);
		if (!now) {
			root = rs(root);
			fa[root] = 0;
		} else {
			Splay(now);
			SetSon(rs(rs(root)), root, 1);
			PushUp(root);
		}
		//No need to free the target node
	}
	int Find(int v) {
		auto it = node.lower_bound(make_pair(v, 0));
		return it != node.end() && it->first == v ? it->second : 0;
	}
	int QueryMinBefore(int rt) {
		Splay(rt);
		return ls(rt) ? mini[ls(rt)] : 0x3f3f3f3f;
	}
};