struct SEG {
	int siz, sum, ms, lms, rms;
	SEG(){}
	SEG(int v) {
		siz = 1;
		sum = ms = lms = rms = v;
	}
	SEG(int _siz, int _sum, int _ms, int _lms, int _rms) {
		siz = _siz;
		sum = _sum;
		ms = _ms;
		lms = _lms;
		rms = _rms;
	}
	SEG operator + (const SEG& rhs) const {
		return SEG(siz + rhs.siz,
			sum + rhs.sum,
			max(max(ms, rhs.ms), rms + rhs.lms),
			max(lms, sum + rhs.lms),
			max(rhs.rms, rhs.sum + rms));
	}
	SEG& operator = (int v) {
		sum = v * siz;
		ms = lms = rms = (v < 0 ? v : sum);
		return *this;
	}
};
struct SPLAY {
	int c[MAXN][2], fa[MAXN], tot, root, val[MAXN], lazy_replace[MAXN];
	SEG segs[MAXN];
	bool lazy_reverse[MAXN];

#define ls(rt) c[rt][0]
#define rs(rt) c[rt][1]
	//vs[1] and vs[n] is 0, which is extra elements serve as boundary
	void Init(int vs[], int n) {
		root = tot = 0;
		Build(root, 0, 1, n, vs);
	}
	void PushUp(int rt) {
		if (ls(rt) && rs(rt)) {
			segs[rt] = segs[ls(rt)] + SEG(val[rt]) + segs[rs(rt)];
		} else if (ls(rt)) {
			segs[rt] = segs[ls(rt)] + SEG(val[rt]);
		} else if (rs(rt)) {
			segs[rt] = SEG(val[rt]) + segs[rs(rt)];
		} else {
			segs[rt] = SEG(val[rt]);
		}
		//segs[rt] = (ls(rt) ? segs[ls(rt)] : SEG(0)) + SEG(val[rt]) + (rs(rt) ? segs[rs(rt)] : SEG(0));
	}
	void Build(int& rt, int f, int l, int r, int vs[]) {
		if (l <= r) {
			int mid = (l + r) >> 1;
			rt = ++tot;
			fa[rt] = f;
			segs[rt].siz = 1;
			segs[rt] = val[rt] = vs[mid];
			lazy_replace[rt] = INT_MIN;
			lazy_reverse[rt] = false;
			Build(ls(rt), rt, l, mid-1, vs);
			Build(rs(rt), rt, mid+1, r, vs);
			PushUp(rt);
		} else {
			rt = 0;
		}
	}
	inline bool Side(int rt) {
		return rt == rs(fa[rt]);
	}
	void ModifySon_reverse(int s) {
		if (s) {
			lazy_reverse[s] ^= 1;
			swap(segs[s].lms, segs[s].rms);
		}
	}
	void ModifySon_replace(int s, int lazy) {
		if (s) {
			lazy_replace[s] = val[s] = lazy;
			segs[s] = lazy;
		}
	}
	void PushDown(int rt) {
		if (lazy_reverse[rt]) {
			swap(ls(rt), rs(rt));
			ModifySon_reverse(ls(rt));
			ModifySon_reverse(rs(rt));
			lazy_reverse[rt] = false;
		}
		if (lazy_replace[rt] != INT_MIN) {
			ModifySon_replace(ls(rt), lazy_replace[rt]);
			ModifySon_replace(rs(rt), lazy_replace[rt]);
			lazy_replace[rt] = INT_MIN;
		}
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

	int QueryKth(int k) {
		int rt = root;
		while (rt) {
			PushDown(rt);
			if (segs[ls(rt)].siz + 1 == k) {
				return rt;
			} else if (segs[ls(rt)].siz >= k) {
				rt = ls(rt);
			} else {
				k -= segs[ls(rt)].siz + 1;
				rt = rs(rt);
			}
		}
		return 0;
	}

	//Insert behind the k_th number
	void Insert(int k, int vs[], int n) {
		int l = QueryKth(k + 1), r = QueryKth(k + 2);
		Splay(l);
		Splay(r, l);
		Build(ls(r), r, 1, n, vs);
		PushUp(r);
		PushUp(l);
	}
#define GetBound \
		int l = QueryKth(L), r = QueryKth(R+2);\
		Splay(l);\
		Splay(r, l)

	void Del(int L, int R) {
		GetBound;
		ls(r) = 0;
		PushUp(r);
		PushUp(l);
	}
	void Replace(int L, int R, int v) {
		GetBound;
		ModifySon_replace(ls(r), v);
		PushUp(r);
		PushUp(l);
	}
	void Reverse(int L, int R) {
		GetBound;
		ModifySon_reverse(ls(r));
		PushUp(r);
		PushUp(l);
	}
	int QuerySum(int L, int R) {
		GetBound;
		return segs[ls(r)].sum;
	}
	int QueryMaxSum(int L, int R) {
		GetBound;
		return segs[ls(r)].ms;
	}
};

