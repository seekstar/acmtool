struct TwoSAT {
	GRAPH g;
	bool mark[MAXN * 2];
	int rec[MAXN * 2], top;
	void Init(int n) {
		g.Init((n+1) * 2);
		memset(mark, 0, (2 * (n+1)) * sizeof(bool));
	}
	inline void AddDeduction(int x, bool xv, int y, bool yv) {
		g.AddDi(x * 2 + xv, y * 2 + yv);
	}
	bool dfs(int x) {
		if (mark[x ^ 1])
			return false;
		if (mark[x])
			return true;
		mark[x] = true;
		rec[top++] = x;
		for (int v : g.s[x])
			if (!dfs(v))
				return false;
		return true;
	}
	bool solve(int n) {
		for (int i = 0; i < n * 2; i += 2) {
			if (mark[i] || mark[i + 1])
				continue;
			top = 0;
			if (!dfs(i)) {
				while (top)
					mark[rec[--top]] = false;
				if (!dfs(i+1))
					return false;
			}
		}
		return true;
	}
};