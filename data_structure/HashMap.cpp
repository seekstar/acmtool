//100003, 300017, 1000033, 5000011, 30000023
template <typename key_t, typename val_t>
struct HashMap {
	const static int p = ;	//greater than the number of insertions
	const static val_t NOT_FOUND = numeric_limits<val_t>::min();
	int hd[p], nxt[p], tot;
	key_t keys[p];
	val_t vals[p];
	void Init() {
		tot = 0;
		memset(hd, -1, sizeof(hd));
	}
	//find first if you do not want to shadow
	void emplace_shadow(key_t key, val_t val) {
		//Shadow the previous one
		int ha = key % p;
		nxt[++tot] = hd[ha];
		hd[ha] = tot;
		keys[tot] = key;
		vals[tot] = val;
	}
	val_t find(key_t key) {
		int ha = key % p;
		for (int e = hd[ha]; ~e; e = nxt[e])
			if (keys[e] == key)
				return vals[e];
		return NOT_FOUND;
	}
};



template <typename T, int p> struct MyHash;
template <int p>
struct MyHash<pii, p> {
    int operator () (const pii& x) const {
        return ((LL)x.first << 32 + x.second) % p;
    }
};

struct SLOPE_EQ {
    bool operator () (const VEC& a, const VEC& b) const {
        return (LL)a.y * b.x == (LL)a.x * b.y;
    }
};

template <int p>
struct INVS {
    int invs[p];
    INVS() {
        GetInvs(invs, p, p-1);
    }
};
template <int p>
struct SLOPE_HASH {
    static INVS<p> helper;
#define invs helper.invs
    int operator () (VEC x) const {
        x.x %= p;
        x.y %= p;
        if (x.x < 0) {
            x.x = -x.x;
            x.y = -x.y;
        }
        return x.x ? Sub(x.y, p) * invs[x.x] % p : 0;
    }
};
template <int p>
INVS<p> SLOPE_HASH<p>::helper;

//2027, 100003, 300017, 1000033, 5000011, 30000023
template <int p, typename key_t, typename val_t, typename Hash = MyHash<key_t, p>, typename Pred = equal_to<key_t> >
struct HashMap {
    Hash hasher;
    Pred key_eq;
    val_t NOT_FOUND = numeric_limits<val_t>::min();
    int hd[p], nxt[p], tot;
    key_t keys[p];
    val_t vals[p];
    void Init() {
        tot = 0;
        memset(hd, -1, sizeof(hd));
    }
    //find first if you do not want to shadow
    void emplace_shadow(const key_t& key, const val_t& val) {
        //Shadow the previous one
        int ha = hasher(key);
        nxt[++tot] = hd[ha];
        hd[ha] = tot;
        keys[tot] = key;
        vals[tot] = val;
    }
    val_t& find(key_t key) {
        int ha = hasher(key);
        for (int e = hd[ha]; ~e; e = nxt[e])
            if (key_eq(keys[e], key))
                return vals[e];
        return NOT_FOUND;
    }
};
