#define MAX_NODE_SPLAY (MAXM << 2)
struct SPLAY {
	int c[MAX_NODE_SPLAY][2], fa[MAX_NODE_SPLAY], siz[MAX_NODE_SPLAY], tot, root;
	int val[MAX_NODE_SPLAY];
	map<int, int> node;	//node[i] is the position of the node whose value is i

#define ls(rt) c[rt][0]
#define rs(rt) c[rt][1]
	void NewVirtual(int& rt, int f, int sz, int first_val) {
		if (sz) {
			rt = ++tot;
			siz[rt] = sz;
			fa[rt] = f;
			val[rt] = -first_val;
			node[val[rt]] = rt;
		} else {
			rt = 0;
		}
	}
	void Init(int n) {
		tot = 0;
		NewVirtual(root, 0, n, 1);
	}
	void PushUp(int rt) {
		siz[rt] = 1 + (ls(rt) ? siz[ls(rt)] : 0) + (rs(rt) ? siz[rs(rt)] : 0);
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

	//Use the k_th node of the group of the virtual nodes
	void AssignVirtual(int rt, int k) {
		if (1 == k)
			node.erase(val[rt]);
		NewVirtual(c[rt][0], rt, k-1, -val[rt]);
		val[rt] = -val[rt] + k - 1;
		node[val[rt]] = rt;
		NewVirtual(c[rt][1], rt, siz[rt] - k, val[rt]+1);
		if (1 == k && c[rt][1])
			node[val[c[rt][1]]] = c[rt][1];
	}
	int QueryKth(int k) {
		int rt = root;
		while (rt) {
			if (val[rt] < 0) {
				AssignVirtual(rt, k);
				return rt;
			}
			else if (siz[ls(rt)] + 1 == k) {
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

	int find(int v) {
		auto it = node.find(v);
		int rt;
		if (node.end() == it) {
			it = node.lower_bound(-v);
			rt = it->second;
			AssignVirtual(rt, v + val[rt] + 1);	//The "it" will change
		} else {
			rt = it->second;
		}
		Splay(rt);
		return rt;
	}
	int QuerySmaller() {
		return siz[ls(root)];
	}
	int QuerySmaller(int v) {
		find(v);
		return QuerySmaller();
	}

	//now mustn't be virtual node
	int FindPreOrNext(int now, bool nex) {
		if (!c[now][nex]) return 0;
		nex = !nex;
		for (now = c[now][!nex]; val[now] < 0 || c[now][nex]; now = c[now][nex]) {
			if (val[now] < 0) {
				AssignVirtual(now, nex ? siz[now] : 1);
				break;
			}
		}
		return now;
	}
	//return the rank before the operation
	void Top(int v) {
		int now = find(v);
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
		int now = find(v);
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

	//return the rank
	int ModifyVal(int ori, int v) {
		int rt = find(ori);
		val[rt] = v;
		node.erase(ori);
		node[val[rt]] = rt;
		return siz[ls(rt)]+1;
	}
};


