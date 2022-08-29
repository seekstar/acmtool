// 307ms. Actuall slower than the version with parent pointer
template <typename T>
struct SplayNode {
	int c[2];
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

	void Init() {
		root = tot = 0;
	}
	bool Side(int rt) {
		return rt == rc(s[rt].pa);
	}
	void PushUp(int rt) {
		s[rt].siz = s[rt].cnt;
		// if (lc(rt))
		s[rt].siz += s[lc(rt)].siz;
		// if (rc(rt))
		s[rt].siz += s[rc(rt)].siz;
	}
	void Init(int rt, const T& key) {
		lc(rt) = rc(rt) = 0;
		s[rt].siz = s[rt].cnt = 1;
		s[rt].key = key;
	}
	void SetSon(int x, int f, int side) {
		// if (f)
		s[f].c[side] = x;
	}
	// y is the parent of x
	// Will update y.scnt
    // Dirty: root, x.scnt, x <-> to
	void __RotateUp(int x, int y, bool side_x) {
		SetSon(s[x].c[!side_x], y, side_x);
		SetSon(y, x, !side_x);
		PushUp(y);
	}
	// Nodes from x to root will be updated
	// Dirty: x.scnt, x <-> path[0]
	void __Splay(int x, std::pair<int, bool>* path, int n) {
		while (n) {
			n -= 1;
			int y = path[n].first;
			bool side_x = path[n].second;
			if (n == 0) {
				__RotateUp(x, y, side_x);
				break;
			}
			n -= 1;
			int z = path[n].first;
			bool side_y = path[n].second;
			if (side_x == side_y) {
				__RotateUp(y, z, side_y);
				__RotateUp(x, y, side_x);
			} else {
				__RotateUp(x, y, side_x);
				__RotateUp(x, z, side_y);
			}
		}
	}
	// Nodes from x to path[0] will be updated
	// Dirty: x <-> path[0]
	void RotateTo(int x, std::pair<int, bool>* path, int n) {
		__Splay(x, path, n);
		PushUp(x);
	}
    // Nodes from cur to root will be updated
	void RotateToRoot(int cur, std::pair<int, bool>* path, int n) {
		RotateTo(cur, path, n);
		root = cur;
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
		int now = root;
		std::vector<std::pair<int, bool>> path;
		while (1) {
			if (s[now].key == key) {
				++s[now].cnt;
				break;
			}
			bool side = s[now].key < key;
			path.emplace_back(now, side);
			now = s[now].c[side];
			if (!now) {
				Init(now = ++tot, key);
				break;
			}
		}
		RotateToRoot(now, path.data(), path.size());
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
		std::vector<std::pair<int, bool>> path;
		size_t ans_depth = 0;
		while (cur != 0) {
			bool side = s[cur].key < key;
			path.emplace_back(cur, side);
			if (side) {
				cur = rc(cur);
			} else {
				ans_depth = path.size();
				cur = lc(cur);
			}
		}
		if (path.empty())
			return 0;
		int prev = path.back().first;
		path.pop_back();
		int ans;
		if (ans_depth <= path.size()) {
			// ans != prev
			RotateTo(prev, path.data() + ans_depth, path.size() - ans_depth);
			path.resize(ans_depth);
			if (path.empty()) {
				root = prev;
				return 0;
			}
			ans = path.back().first;
			bool side = path.back().second;
			path.pop_back();
			SetSon(prev, ans, side);
			// ans.scnt will be updated by rotate_to_root later.
		} else {
			ans = prev;
		}
		RotateToRoot(ans, path.data(), path.size());
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
		int x = root;
		std::vector<std::pair<int, bool> > path;
		while (x) {
			int lcnt = s[lc(x)].siz;
			if (lcnt < k && k <= lcnt + s[x].cnt) {
				RotateToRoot(x, path.data(), path.size());
				return x;
			}
			bool side = lcnt < k;
			path.emplace_back(x, side);
			if (side) {
				k -= s[lc(x)].siz + s[x].cnt;
				x = rc(x);
			} else {
				x = lc(x);
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
