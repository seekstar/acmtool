//Path replace, subtree replace, path sum, subtree sum
struct HLD : public HLD_base {
	SegTree<int> sgt;

	void Init(const GRAPH& g, int rt) {
		HLD_base::Init(g, rt);
		sgt.Init(n);
	}
	void Replace2Rt(int x, int v) {
		while (x) {	//The father of the root is 0
			sgt.Replace(1, 1, n, id[top[x]], id[x], v);
			x = fa[top[x]];
		}
	}
	int Sum2Rt(int x) {
		int ans = 0;
		while (x) {
			ans += sgt.Sum(1, 1, n, id[top[x]], id[x]);
			x = fa[top[x]];
		}
		return ans;
	}
	void ReplaceSubTree(int x, int v) {
		sgt.Replace(1, 1, n, id[x], id[x] + siz[x] - 1, v);
	}
	int SumSubTree(int x) {
		return sgt.Sum(1, 1, n, id[x], id[x] + siz[x] - 1);
	}
};

