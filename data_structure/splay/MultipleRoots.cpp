#define MAX_NODE_SPLAY ((MAXN * 3 + MAXK) << 4)
struct SPLAY {
	int roots[MAXN], c[MAX_NODE_SPLAY][2], fa[MAX_NODE_SPLAY], keys[MAX_NODE_SPLAY], siz[MAX_NODE_SPLAY], tot;

#define ls(rt) c[rt][0]
#define rs(rt) c[rt][1]
	void Init(int n) {
		tot = 0;
		memset(roots, 0, (n+1) * sizeof(int));
		for (int i = 0; i <= n; ++i)
			InitRoot(roots[i]);
	}
	void InitRoot(int& rt) {
		Init(rt = ++tot, INT_MIN);
		Init(rs(rt) = ++tot, INT_MAX);
		fa[rs(rt)] = rt;
		siz[rt] = 2;
	}
	inline bool Side(int rt) {
		return rt == rs(fa[rt]);
	}
	void PushUp(int rt) {
		siz[rt] = 1 + (ls(rt) ? siz[ls(rt)] : 0) + (rs(rt) ? siz[rs(rt)] : 0);
	}
	void Init(int rt, int key) {
		ls(rt) = rs(rt) = fa[rt] = 0;
		siz[rt] = 1;
		keys[rt] = key;
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
		PushUp(f);	//"f" is the son of "now" now.
		PushUp(now);
	}
	//Require that sum[now] is up to date
	void Splay(int now, int to = 0) {
		if (!now) return;
		for (int f = fa[now]; f != to; f = fa[now]) {
			if (fa[f] != to)
				RotateUp(Side(now) == Side(f) ? f : now);
			RotateUp(now);
		}
	}
	
	void Insert(int& rt, int key) {
		int now = rt, f;
		while (1) {
			if (!now) {
				Init(now = ++tot, key);
				SetSon(now, f, keys[f] < key);
				break;
			}
			f = now;
			now = c[now][keys[now] < key];
		}
		Splay(now);
		rt = now;
	}

	int FindPreByKey(int rt, int key) {
		int ans = 0, now = rt;
		while (now) {
			if (keys[now] < key) {
				ans = now;
				now = rs(now);
			} else {
				now = ls(now);
			}
		}
		return ans;
	}
	int FindNextByKey(int rt, int key) {
		int ans = 0, now = rt;
		while (now) {
			if (key < keys[now]) {
				ans = now;
				now = ls(now);
			} else {
				now = rs(now);
			}
		}
		return ans;
	}

	int QuerySize(int& rt, int L, int R) {
		int l = FindPreByKey(rt, L), r = FindNextByKey(rt, R);
		Splay(l);
		rt = l;
		Splay(r, l);
		return ls(r) ? siz[ls(r)] : 0;
	}

	void Del(int& rt, int key) {
		int l = FindPreByKey(rt, key), r = FindNextByKey(rt, key);
		Splay(l);
		rt = l;
		Splay(r, l);
		ls(r) = 0;
		PushUp(r);
		PushUp(l);
	}
};


