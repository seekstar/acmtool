template<typename T>
struct SPLAY {
	int c[MAXN][2], fa[MAXN], keys[MAXN], siz[MAXN], tot, root, val[MAXN];
	T sum[MAXN], lazy[MAXN];

#define ls(rt) c[rt][0]
#define rs(rt) c[rt][1]
	void Init() {
		root = tot = 0;
		Insert(INT_MAX, 0);
		Insert(INT_MIN, 0);
	}
	bool Side(int rt) {
		return rt == rs(fa[rt]);
	}
	void PushUp(int rt) {
		siz[rt] = 1 + (ls(rt) ? siz[ls(rt)] : 0) + (rs(rt) ? siz[rs(rt)] : 0);
		sum[rt] = val[rt] + (ls(rt) ? sum[ls(rt)] : 0) + (rs(rt) ? sum[rs(rt)] : 0);
	}
	void PushDown(int rt) {
		if (lazy[rt]) {
			if (ls(rt)) {
				sum[ls(rt)] += siz[ls(rt)] * lazy[rt];
				val[ls(rt)] += lazy[rt];
				lazy[ls(rt)] += lazy[rt];
			}
			if (rs(rt)) {
				sum[rs(rt)] += siz[rs(rt)] * lazy[rt];
				val[rs(rt)] += lazy[rt];
				lazy[rs(rt)] += lazy[rt];
			}
			lazy[rt] = 0;
		}
	}
	void Init(int rt, int key, int v) {
		ls(rt) = rs(rt) = fa[rt] = 0;
		siz[rt] = 1;
		keys[rt] = key;
		val[rt] = sum[rt] = v;
		lazy[rt] = 0;
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
		PushUp(f);	//"f" is the son of "now" now.
		PushUp(now);
		if (!fa[now])
			root = now;
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

	void Insert(int key, const T& v) {
		if (!root) {
			Init(root = ++tot, key, v);
		} else {
			int now = root, f;
			while (1) {
				PushDown(now);
				if (!now) {
					Init(now = ++tot, key, v);
					SetSon(now, f, keys[f] < key);
					break;
				}
				f = now;
				now = c[now][keys[now] < key];
			}
			Splay(now);
		}
	}

	int FindPreByKey(int key) {
		int ans = 0, now = root;
		while (now) {
			PushDown(now);
			if (keys[now] < key) {
				ans = now;
				now = rs(now);
			} else {
				now = ls(now);
			}
		}
		return ans;
	}
	int FindNextByKey(int key) {
		int ans = 0, now = root;
		while (now) {
			PushDown(now);
			if (key < keys[now]) {
				ans = now;
				now = ls(now);
			} else {
				now = rs(now);
			}
		}
		return ans;
	}
#define GetBound \
		int l = FindPreByKey(L), r = FindNextByKey(R);\
		Splay(l);\
		Splay(r, root)

	//delete all elements whose keys are in [L, R]
	void Del(int L, int R) {
		GetBound;
		ls(r) = 0;
		PushUp(r);
		PushUp(l);
	}

	//Return the sum of values of elements whose keys are in [L, R]
	T QuerySum(int L, int R) {
		GetBound;
		return ls(r) ? sum[ls(r)] : 0;
	}

	void Add(int L, int R, int v) {
		GetBound;
		sum[ls(r)] += v * siz[ls(r)];
		val[ls(r)] += v;
		lazy[ls(r)] += v;
		PushUp(r);
		PushUp(l);
	}
};
