template <typename T>
struct SplayNode {
	SplayNode<T>* c[2];
	SplayNode<T>* pa;
	int cnt;
	int scnt;
	T key;
	SplayNode(const T& k) : c{NULL, NULL}, pa(NULL), cnt(1), scnt(1), key(k) {}
};

template<typename T>
struct Splay {
	SplayNode<T>* root;

	void Init() {
		root = NULL;
	}
	void Free() {
		FreeSubTree(root);
	}
	void FreeSubTree(SplayNode<T>* rt) {
		if (rt == NULL)
			return;
		FreeSubTree(rt->c[0]);
		FreeSubTree(rt->c[1]);
		delete rt;
	}
	bool Side(SplayNode<T>* x) {
		return x == x->pa->c[1];
	}
	void PushUp(SplayNode<T>* rt) {
		rt->scnt = rt->cnt;
		if (rt->c[0])
			rt->scnt += rt->c[0]->scnt;
		if (rt->c[1])
			rt->scnt += rt->c[1]->scnt;
	}
	void SetSon(SplayNode<T>* x, SplayNode<T>* f, bool side) {
		if (f)
			f->c[side] = x;
		if (x)
			x->pa = f;
	}
	// y is the parent of x
	// Will update y.scnt
    // Dirty: root, x.scnt
	void __RotateUp(SplayNode<T>* x, SplayNode<T>* y, bool side_x) {
		SetSon(x->c[!side_x], y, side_x);
		SetSon(y, x, !side_x);
		PushUp(y);
	}
	// Nodes from x to root will be updated
    // Dirty: x <-> to
	void __Splay(SplayNode<T>* x, SplayNode<T>* to) {
		SplayNode<T>* y = x->pa;
		if (y == to) {
			PushUp(x);
			return;
		}
		bool side_x = Side(x);
		while (y != to) {
			SplayNode<T>* z = y->pa;
			if (z == to) {
				__RotateUp(x, y, side_x);
				break;
			}
			SplayNode<T>* z_pa = z->pa;
			bool side_y = Side(y);
			bool side_z;
			if (z_pa != to)
				side_z = Side(z);
			else
				side_z = false; // Any value is okay.
			if (side_x == side_y) {
				__RotateUp(y, z, side_y);
				__RotateUp(x, y, side_x);
			} else {
				__RotateUp(x, y, side_x);
				__RotateUp(x, z, side_y);
			}
			y = z_pa;
			side_x = side_z;
		}
		PushUp(x);
	}
    // Nodes from cur to root will be updated
	void RotateToRoot(SplayNode<T>* cur) {
		if (cur == NULL)
			return;
		__Splay(cur, NULL);
		root = cur;
		cur->pa = NULL;
	}
	void RotateTo(SplayNode<T>* x, SplayNode<T>* to, bool side) {
		if (to == NULL) {
			RotateToRoot(x);
		} else {
			__Splay(x, to);
			SetSon(x, to, side);
		}
	}

	size_t size() {
		if (root) {
			return root->scnt;
		} else {
			return 0;
		}
	}
	// The new node will be the root
	void Insert(const T& key) {
		if (!root) {
			root = new SplayNode<T>(key);
			return;
		}
		SplayNode<T>* now = root;
		SplayNode<T>* f;
		bool side;
		while (1) {
			if (now->key == key) {
				now->cnt += 1;
				break;
			}
			f = now;
			side = now->key < key;
			now = now->c[side];
			if (now == NULL) {
				now = new SplayNode<T>(key);
				SetSon(now, f, side);
				break;
			}
		}
		RotateToRoot(now);
	}

	// Find the first node whose value >= key
	// If found, then the node will be the root and returned.
	// Otherwise (all nodes < key), return 0
	SplayNode<T>* lower_bound(const T& key) {
		SplayNode<T>* cur = root;
		SplayNode<T>* prev = NULL;
		SplayNode<T>* ans = NULL;
		while (cur != NULL) {
			prev = cur;
			if (cur->key < key) {
				cur = cur->c[1];
			} else {
				ans = cur;
				cur = cur->c[0];
			}
		}
		if (prev != ans)
			RotateTo(prev, ans, false);
		RotateToRoot(ans);
		return ans;
	}

    // The target node will be the root
	SplayNode<T>* QueryKth(int k) {
		SplayNode<T>* rt = root;
		while (rt) {
			int lcnt;
			if (rt->c[0]) {
				lcnt = rt->c[0]->scnt;
			} else {
				lcnt = 0;
			}
			if (lcnt < k) {
				if (lcnt + rt->cnt >= k) {
					RotateToRoot(rt);
					return rt;
				}
				k -= lcnt + rt->cnt;
				rt = rt->c[1];
			} else {
				rt = rt->c[0];
			}
		}
		assert(0);
		return 0;
	}
	int DelSmaller(const T& key) {
		SplayNode<T>* rt = lower_bound(key);
		if (rt == NULL) {
			if (root) {
				int deleted = root->scnt;
				Free();
				root = NULL;
				return deleted;
			} else {
				return 0;
			}
		}
		if (rt->c[0]) {
			int deleted = rt->c[0]->scnt;
			FreeSubTree(rt->c[0]);
			rt->c[0] = NULL;
			PushUp(rt);
			return deleted;
		} else {
			return 0;
		}
	}

	void PrintTree(SplayNode<T>* rt, std::string& str, int(PrintNode)(T)) {
        int rec = str.length();
        int len;
        if (rt) {
            len = PrintNode(rt->key);
            printf("---");
            str.append(len, ' ');
            str.append(" | ");
            PrintTree(rt->c[0], str, PrintNode);
            printf("%s\n", str.c_str());
            str[str.length()-1] = str[str.length()-2] = '-';
            printf("%s", str.c_str());

            str[str.length()-1] = str[str.length()-2] = ' ';
            PrintTree(rt->c[1], str, PrintNode);

            str.resize(rec);
        } else {
            puts("/\\");
        }
    }
    void PrintTree(SplayNode<T>* rt, int(PrintNode)(T)) {
        std::string str;
        PrintTree(rt, str, PrintNode);
    }
    void PrintBST(int(PrintNode)(T)) {
        PrintTree(root, PrintNode);
    }
};
