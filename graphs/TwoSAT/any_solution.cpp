GRAPH g;
int root[2*MAXN], low[2*MAXN], dfn[2*MAXN], sta[2 * MAXN], top, dfnc, rootcnt;	// rootcnt is new
bool in[2*MAXN];
void tarjan(int u) {
	low[u] = dfn[u] = ++dfnc;
	sta[++top] = u;
	in[u] = true;
	for (int v : g.s[u]) {
		if (!dfn[v]) {
			tarjan(v);
			low[u] = min(low[u], low[v]);
		} else if (in[v]) {
			low[u] = min(low[u], dfn[v]);
		}
	}
	if (dfn[u] == low[u]) {
		int v;
		++rootcnt;
		do {
			v = sta[top--];
			in[v] = false;
			root[v] = rootcnt;
		} while (u != v);
	}
}

void Init(int n) {
	g.Init(n * 2);
	memset(dfn, 0, 2 * n * sizeof(int));
	memset(in, 0, 2 * n * sizeof(bool));
	dfnc = rootcnt = top = 0;
}
void AddDeduction(int i, int vi, int j, int vj) {
	g.AddDi(i * 2 + vi, j * 2 + vj);
}
// 0 <= i,j < n
void AddOr(int i, bool vi, int j, bool vj) {
	AddDeduction(i, !vi, j, vj);
	AddDeduction(j, !vj, i, vi);
}
bool solve(bool val[], int n) {
	for (int i = 0; i < 2 * n; ++i)
		if (!dfn[i])
			tarjan(i);
	for (int i = 0; i < 2 * n; i += 2)
		if (root[i] == root[i + 1])
			return false;
	for (int i = 0; i < n; ++i) {
		val[i] = root[i * 2] > root[i * 2 + 1];
	}
	return true;
}