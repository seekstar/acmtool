//Replace at a point, get the sum and the maximum of values of a type in the path
template<typename T>
struct HLD : public HLD_base {
	DynamicSegTree dsgt;
	
	void Init(const GRAPH& g, int rt, int type[], int val[]) {
		HLD_base::Init(g, rt);
		dsgt.Init(maxtype);
		for (int i = 1; i <= n; ++i)
			Update(type[i], i, val[i]);
	}
	//The sum of the values of type k in the path from x to y
	T SumInPath(int x, int y, int k) {
		T ans = 0;
		while (top[x] != top[y]) {
			if (depth[top[x]] < depth[top[y]])
				swap(x, y);
			ans += dsgt.Sum(dsgt.roots[k], 1, n, id[top[x]], id[x]);
			x = fa[top[x]];
		}
		if (depth[x] > depth[y])
			swap(x, y);
		ans += dsgt.Sum(dsgt.roots[k], 1, n, id[x], id[y]);
		return ans;
	}
	T MaxInPath(int x, int y, int k) {
		T ans = MINVAL;
		while (top[x] != top[y]) {
			if (depth[top[x]] < depth[top[y]])
				swap(x, y);
			ans = max(ans, dsgt.Max(dsgt.roots[k], 1, n, id[top[x]], id[x]));
			x = fa[top[x]];
		}
		if (depth[x] > depth[y])
			swap(x, y);
		ans = max(ans, dsgt.Max(dsgt.roots[k], 1, n, id[x], id[y]));
		return ans;
	}
	//Update the value of index x of type k to v
	void Update(int k, int x, T v) {
		dsgt.Update(dsgt.roots[k], 1, n, id[x], v);
	}
};

