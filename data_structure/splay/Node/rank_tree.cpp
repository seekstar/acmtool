template <typename T>
struct SplayNode {
	int c[2];
	int pa;
	int cnt;
	int siz;
	T key;
};

template<typename T>
struct Splay {
	//0 is invalid
	SplayNode<T> s[MAXN];
	int tot, root;

	inline int& lc(int rt) {
		return s[rt].c[0];
	}
	inline int& rc(int rt) {
		return s[rt].c[1];
	}
	inline int& pa(int rt) {
		return s[rt].pa;
	}

	void Init() {
		root = tot = 0;
	}
	bool Side(int rt) {
		return rt == rc(pa(rt));
	}
	void PushUp(int rt) {
		s[rt].siz = s[rt].cnt;
		// if (lc(rt))
		s[rt].siz += s[lc(rt)].siz;
		// if (rc(rt))
		s[rt].siz += s[rc(rt)].siz;
	}
	void Init(int rt, const T& key) {
		lc(rt) = rc(rt) = pa(rt) = 0;
		s[rt].siz = s[rt].cnt = 1;
		s[rt].key = key;
	}
	void SetSon(int x, int f, int side) {
		// if (f)
		s[f].c[side] = x;
		// if (x)
		pa(x) = f;
	}
	// y is the parent of x
	// Will update y.scnt
    // Dirty: root, x.scnt
	void __RotateUp(int x, int y, bool side_x) {
		SetSon(s[x].c[!side_x], y, side_x);
		SetSon(y, x, !side_x);
		PushUp(y);
	}
	// Nodes from x to root will be updated
    // Dirty: x <-> to
	void __Splay(int x, int to) {
		if (!x) return;
		int y = pa(x);
		bool side_x = Side(x);
		while (y != to) {
			int z = pa(y);
			if (z == to) {
				__RotateUp(x, y, side_x);
				break;
			}
			int z_pa = pa(z);
			bool side_y = Side(y);
			bool side_z = Side(z);
			if (side_x == side_y) {
				__RotateUp(y, z, side_y);
				__RotateUp(x, y, side_x);
			} else {
				__RotateUp(x, y, side_x);
				__RotateUp(x, z, side_y);
			}
			side_x = side_z;
			y = z_pa;
		}
		PushUp(x);
	}
    // Nodes from cur to root will be updated
	void RotateToRoot(int cur) {
		if (cur == 0)
			return;
		__Splay(cur, 0);
		root = cur;
		pa(cur) = 0;
		PushUp(cur);
	}
	void RotateTo(int x, int to, bool side) {
		if (to == 0) {
			RotateToRoot(x);
		} else {
			__Splay(x, to);
			SetSon(x, to, side);
		}
	}

	size_t size() {
		return s[root].siz;
	}
	// The new node will be the root
	void Insert(const T& key) {
		if (!root) {
			Init(root = ++tot, key);
			return;
		}
		int now = root, f;
		bool side;
		while (1) {
			if (!now) {
				Init(now = ++tot, key);
				SetSon(now, f, side);
				break;
			} else if (s[now].key == key) {
				++s[now].cnt;
				break;
			}
			f = now;
			side = s[now].key < key;
			now = s[now].c[side];
		}
		RotateToRoot(now);
	}

	// The target node will be the root
	// int find(const T& key) {
	// 	int now = root;
	// 	while (now && keys[now] != key)
	// 		now = c[now][keys[now] < key];
	// 	RotateToRoot(now);
	// 	return now;
	// }
	// Find the first node whose value >= key
	// If found, then the node will be the root and returned.
	// Otherwise (all nodes < key), return 0
	int lower_bound(const T& key) {
		int cur = root;
		int prev = 0, ans = 0;
		while (cur != 0) {
			prev = cur;
			if (s[cur].key < key) {
				cur = rc(cur);
			} else {
				ans = cur;
				cur = lc(cur);
			}
		}
		if (prev != ans)
			RotateTo(prev, ans, false);
		RotateToRoot(ans);
		return ans;
	}
	// int FindPreOrNext(int now, bool nex) const {
	// 	if (!c[now][nex]) return 0;
	// 	nex = !nex;
	// 	for (now = c[now][!nex]; c[now][nex]; now = c[now][nex]);
	// 	return now;
	// }
	// void DelRoot() {
	// 	int now = FindPreOrNext(root, false);
	// 	if (!now) {
	// 		root = rc(root);
	// 		fa[root] = 0;
	// 	} else {
	// 		RotateToRoot(now);
	// 		SetSon(rc(rc(root)), root, 1);
	// 		PushUp(root);
	// 	}
	// 	//No need to free the target node
	// }
	// void Del(const T& key) {
	// 	int now = find(key);
	// 	if (!now) return;
	// 	if (cnt[root] > 1) {
	// 		--cnt[root];
	// 		--siz[root];
	// 	} else if (!lc(root) || !rc(root)) {
	// 		root = lc(root) + rc(root);
	// 		fa[root] = 0;	//Even if root == 0, it does no harm
	// 		//No need to free the target node
	// 	} else {
	// 		DelRoot();
	// 	}
	// }

    // The target node will be the root
	int QueryKth(int k) {
		int rt = root;
		while (rt) {
			if (s[lc(rt)].siz < k) {
				if (s[lc(rt)].siz + s[rt].cnt >= k) {
					RotateToRoot(rt);
					return rt;
				}
				k -= s[lc(rt)].siz + s[rt].cnt;
				rt = rc(rt);
			} else {
				rt = lc(rt);
			}
		}
		assert(0);
		return 0;
	}
	// int QuerySmaller(const T& key) {
	// 	int now = find(key);
	// 	bool flag = false;
	// 	if (!now) {
	// 		Insert(key);
	// 		flag = true;
	// 	}
	// 	int ans = lc(root) ? siz[lc(root)] : 0;
	// 	if (flag) DelRoot();
	// 	return ans;
	// }
	// T QueryPreOrNext(const T& key, bool nex) {
	// 	int now = find(key);
	// 	bool flag = false;
	// 	if (!now) {
	// 		Insert(key);
	// 		now = root;
	// 		flag = true;
	// 	}
	// 	if (!c[now][nex]) {
	// 		if (flag)
	// 			Del(key);
	// 		return -1;
	// 	}
	// 	now = FindPreOrNext(now, nex);
	// 	if (flag)
	// 		Del(key);
	// 	return now >= 0 ? keys[now] : -1;
	// }
	int DelSmaller(const T& key) {
		int rt = lower_bound(key);
		if (rt == 0) {
			int deleted = s[root].siz;
			root = 0;
			return deleted;
		}
		int deleted = s[lc(rt)].siz;
		lc(rt) = 0;
		PushUp(rt);
		return deleted;
	}
};
