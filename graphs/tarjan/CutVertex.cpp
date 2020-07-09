GRAPH g;
int cut[MAXN], num;

int low[MAXN], dfn[MAXN], dfnc;
stack<int> sta;

void tarjan(int u, int fa) {
	low[u] = dfn[u] = ++dfnc;
	sta.push(u);
	int flags = 0;
	for (int v : g.s[u]) {
		if (!dfn[v]) {
			tarjan(v, u);
			low[u] = min(low[u], low[v]);
			if (low[v] >= dfn[u])
				++flags;
		} else {
			low[u] = min(low[u], dfn[v]);
		}
	}
	if (flags >= (-1 == fa ? 2 : 1))
		cut[num++] = u;
}
void GetCutVertex() {
	dfnc = num = 0;
	memset(dfn, 0, g.s.size() * sizeof(int));
	for (int i = 1; i < (int)g.s.size(); ++i) {
		if (!dfn[i]) {
			tarjan(i, -1);
		}
	}
}
