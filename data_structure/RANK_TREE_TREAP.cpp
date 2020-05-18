template<typename T>
struct TREAP {
	//c[][0] is left child
	//cnt[] is the number of values of the node.
	//siz[] is the number of values in the subtree
	int root, c[MAXN][2], cnt[MAXN], siz[MAXN], tot, p[MAXN];	//p:priority
	T val[MAXN];

	void Init() {
		root = tot = 0;
	}
	void maintain(int rt) {
		siz[rt] = siz[c[rt][0]] + siz[c[rt][1]] + cnt[rt];
	}
	//d is direction, d == 1 means right rotate
	void Rotate(int& rt, bool d) {
		int t = c[rt][d^1];
		c[rt][d^1] = c[t][d];
		c[t][d] = rt;
		siz[t] = siz[rt];
		maintain(rt);
		rt = t;
	}

	//Return the number of values that are smaller than key
	int QuerySmaller(const T& key) {
		int rt = root, ans = 0;
		while (rt) {
			if (val[rt] == key) {
				return ans + siz[c[rt][0]];
			} else if (key < val[rt]) {
				rt = c[rt][0];
			} else {
				ans += siz[c[rt][0]] + cnt[rt];
				rt = c[rt][1];
			}
		}
		return ans;	//key do not exist
	}

	T QueryKth(int k) {
		int rt = root;
		while (rt) {
			if (siz[c[rt][0]] < k && siz[c[rt][0]] + cnt[rt] >= k) {
				return val[rt];
			} else if (siz[c[rt][0]] >= k) {
				rt = c[rt][0];
			} else {
				k -= siz[c[rt][0]] + cnt[rt];
				rt = c[rt][1];
			}
		}
		return -1;
	}

	//The largest value which is smaller than "key"
	T QueryPre(const T& key) {
		int rt = root;
		T ans = -1;	//if do not exist
		while (rt) {
			if (val[rt] < key) {
				ans = val[rt];
				rt = c[rt][1];
			} else {
				rt = c[rt][0];
			}
		}
		return ans;
	}

	//The smallest value which is larger than "key"
	T QueryNext(const T& key) {
		int rt = root;
		T ans = -1;	//if do not exist
		while (rt) {
			if (key < val[rt]) {
				ans = val[rt];
				rt = c[rt][0];
			} else {
				rt = c[rt][1];
			}
		}
		return ans;
	}

	void Insert(int& rt, const T& key) {
		if (!rt) {
			rt = ++tot;
			c[rt][0] = c[rt][1] = 0;
			val[rt] = key;
			p[rt] = rand();
			siz[rt] = cnt[rt] = 1;
			return;
		}
		++siz[rt];
		if (val[rt] == key) {
			++cnt[rt];
			return;
		}
		bool d = val[rt] < key;
		Insert(c[rt][d], key);
		if (p[c[rt][d]] > p[rt])
			Rotate(rt, d^1);
	}
	void Insert(const T& key) {
		Insert(root, key);
	}
	
	void Del(int& rt, const T& key) {
		if (!rt) return;
		if (val[rt] == key) {
			if (cnt[rt] > 1) {
				--cnt[rt];
				--siz[rt];
			} else if (!c[rt][0] || !c[rt][1]) {
				rt = c[rt][0] + c[rt][1];
			} else {
				Rotate(rt, p[c[rt][0]] > p[c[rt][1]]);
				Del(rt, key);
			}
		} else {
			--siz[rt];
			Del(c[rt][val[rt] < key], key);
		}
	}
	void Del(const T& key) {
		Del(root, key);
	}
};

