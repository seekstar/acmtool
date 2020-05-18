template<typename T>
struct SPLAY {
	//0 is invalid
	int c[MAXN][2], fa[MAXN], cnt[MAXN], siz[MAXN], tot, root;
	T keys[MAXN];

#define ls(rt) c[rt][0]
#define rs(rt) c[rt][1]
	void Init() {
		root = tot = 0;
	}
	bool Side(int rt) {
		return rt == rc(fa[rt]);
	}
	void PushUp(int rt) {
		siz[rt] = cnt[rt];
		if (lc(rt))
			siz[rt] += siz[lc(rt)];
		if (rc(rt))
			siz[rt] += siz[rc(rt)];
	}
	void Init(int rt, const T& key) {
		lc(rt) = rc(rt) = fa[rt] = 0;
		siz[rt] = cnt[rt] = 1;
		keys[rt] = key;
	}
	void SetSon(int x, int f, int s) {
		if (f) c[f][s] = x;
		if (x) fa[x] = f;
	}
	//Will update siz[now] and siz[fa[now]]
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
	//Require that cnt[now] is up to date
	void Splay(int now, int to = 0) {
		if (!now) return;
		for (int f = fa[now]; f != to; f = fa[now]) {
			if (fa[f] != to)
				RotateUp(Side(now) == Side(f) ? f : now);
			RotateUp(now);
		}
	}

	//The new node will be the root
	void Insert(const T& key) {
		if (!root) {
			Init(root = ++tot, key);
		} else {
			int now = root, f;
			while (1) {
				if (!now) {
					Init(now = ++tot, key);
					fa[now] = f;
					c[f][keys[f] < key] = now;
					break;
				} else if (keys[now] == key) {
					++cnt[now];
					break;
				}
				f = now;
				now = c[now][keys[now] < key];
			}
			Splay(now);
		}
	}

	//The target node will be the root
	int find(const T& key) {
		int now = root;
		while (now && keys[now] != key)
			now = c[now][keys[now] < key];
		Splay(now);
		return now;
	}
	int FindPreOrNext(int now, bool nex) const {
		if (!c[now][nex]) return 0;
		nex = !nex;
		for (now = c[now][!nex]; c[now][nex]; now = c[now][nex]);
		return now;
	}
	void DelRoot() {
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
	void Del(const T& key) {
		int now = find(key);
		if (!now) return;
		if (cnt[root] > 1) {
			--cnt[root];
			--siz[root];
		} else if (!lc(root) || !rc(root)) {
			root = lc(root) + rc(root);
			fa[root] = 0;	//Even if root == 0, it does no harm
			//No need to free the target node
		} else {
			DelRoot();
		}
	}

	T QueryKth(int k) {
		int rt = root;
		while (rt) {
			if (siz[c[rt][0]] < k && siz[c[rt][0]] + cnt[rt] >= k) {
				return keys[rt];
			} else if (siz[c[rt][0]] >= k) {
				rt = c[rt][0];
			} else {
				k -= siz[c[rt][0]] + cnt[rt];
				rt = c[rt][1];
			}
		}
		return -1;
	}
	int QuerySmaller(const T& key) {
		int now = find(key);
		bool flag = false;
		if (!now) {
			Insert(key);
			flag = true;
		}
		int ans = lc(root) ? siz[lc(root)] : 0;
		if (flag) DelRoot();
		return ans;
	}
	T QueryPreOrNext(const T& key, bool nex) {
		int now = find(key);
		bool flag = false;
		if (!now) {
			Insert(key);
			now = root;
			flag = true;
		}
		if (!c[now][nex]) {
			if (flag)
				Del(key);
			return -1;
		}
		now = FindPreOrNext(now, nex);
		if (flag)
			Del(key);
		return now >= 0 ? keys[now] : -1;
	}
};

