int root[MAXN];
GRAPH g;
void StrongConnected();
void shrink(GRAPH& ng, bool saved[], int newval[], const int val[]) {
	ng.Init(g.s.size() - 1);
	StrongConnected();
	memset(newval, 0, g.s.size() * sizeof(int));
	for (int i = 1; i < (int)g.s.size(); ++i) {
		int r = root[i];
		newval[r] += val[i];
		for (int j : g.s[i]) {
			int rj = root[j];
			if (rj != r)
				ng.AddDi(r, rj);
		}
	}
	memset(saved, 0, g.s.size() * sizeof(bool));
	for (int i = 1; i < (int)g.s.size(); ++i) {
		saved[root[i]] = true;
	}
}

int low[MAXN], dfn[MAXN], dfnc;
stack<int> sta;
bool in[MAXN];

void tarjan(int u) {
	low[u] = dfn[u] = ++dfnc;
	sta.push(u);
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
		do {
			v = sta.top();
			sta.pop();
			in[v] = false;
			root[v] = u;
		} while (u != v);
	}
}
void StrongConnected() {
	dfnc = 0;
	memset(dfn, 0, g.s.size() * sizeof(int));
	memset(in, 0, g.s.size() * sizeof(bool));
	for (int i = 1; i < (int)g.s.size(); ++i)
		if (!dfn[i])
			tarjan(i);
}