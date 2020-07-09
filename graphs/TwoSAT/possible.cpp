// Capacity of tarjan should be 2 * MAXN
void Init(int n) {
	g.Init(n * 2);
	memset(dfn, 0, 2 * n * sizeof(int));
	memset(in, 0, 2 * n * sizeof(bool));
	dfnc = 0;
}
void AddDeduction(int i, int vi, int j, int vj) {
	g.AddDi(i * 2 + vi, j * 2 + vj);
}
// 0 <= i,j < n
void AddOr(int i, bool vi, int j, bool vj) {
	AddDeduction(i, !vi, j, vj);
	AddDeduction(j, !vj, i, vi);
}
bool solve(int n) {
	for (int i = 0; i < 2 * n; ++i)
		if (!dfn[i])
			tarjan(i);
	for (int i = 0; i < 2 * n; i += 2)
		if (root[i] == root[i + 1])
			return false;
	return true;
}
