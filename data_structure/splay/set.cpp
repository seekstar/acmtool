template <typename T, typename Comp>
struct SPLAY {
    //0 is invalid
    int c[MAXN][2], fa[MAXN], tot, root;
    T keys[MAXN];

#define ls(rt) c[rt][0]
#define rs(rt) c[rt][1]
#define Comp Comp()
    void Init() {
        root = tot = 0;
    }
    bool Side(int rt) {
        return rt == rs(fa[rt]);
    }
    void Init(int rt, const T& key) {
        ls(rt) = rs(rt) = fa[rt] = 0;
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

    //The node will be the root(new or old)
    bool Insert(const T& key) {
        bool ret = true;
        if (!root) {
            Init(root = ++tot, key);
        } else {
            int now = root;
            int f;
            while (true) {
                if (!now) {
                    Init(now = ++tot, key);
                    fa[now] = f;
                    c[f][Comp(keys[f], key)] = now;
                    break;
                } else if (keys[now] == key) {
                    ret = false;
                    break;
                }
                f = now;
                now = c[now][Comp(keys[now], key)];
            }
            Splay(now);
        }
        return ret;
    }

    //The target node will be the root
    int find(const T& key) {
        int now = root;
        while (now && ((Comp(keys[now], key) || Comp(key, keys[now]))))
            now = c[now][Comp(keys[now], key)];
        Splay(now);
        return now;
    }
    //Only go down
    int FindPreOrNext_down(int now, bool nex) const {
        if (!c[now][nex]) return 0;
        nex = !nex;
        for (now = c[now][!nex]; c[now][nex]; now = c[now][nex]);
        return now;
    }
    void DelRoot() {
        int now = FindPreOrNext_down(root, false);
        if (!now) {
            root = rs(root);
            fa[root] = 0;
        } else {
            Splay(now);
            SetSon(rs(rs(root)), root, 1);
        }
        //No need to free the target node
    }
    void Del(const T& key) {
        int now = find(key);
        if (!now) return;
        if (!ls(root) || !rs(root)) {
            root = ls(root) + rs(root);
            fa[root] = 0;	//Even if root == 0, it does no harm
            //No need to free the target node
        } else {
            DelRoot();
        }
    }

    int PreOrNxt(int now, bool nxt) const {
        if (!c[now][nxt]) {
            int f = fa[now];
            while (f && c[f][!nxt] != now) {
                now = f;
                f = fa[now];
            }
            return f;
        } else {
            now = c[now][nxt];
            while (c[now][!nxt]) {
                now = c[now][!nxt];
            }
            return now;
        }
    }
    void erase(int it) {
        Splay(it);
        DelRoot();
    }

    int lower_bound(const T& key, bool nxt) {
        if (!Insert(key)) {
            return root;
        }
        int now = root;
        if (!c[now][nxt]) {
            Del(key);
            return 0;
        }
        now = FindPreOrNext_down(now, nxt);
        Del(key);
        return now;
    }

    int begin() {
        int now = root;
        while (ls(now))
            now = ls(now);
        return now;
    }
    constexpr int end() {
        return 0;
    }
};
