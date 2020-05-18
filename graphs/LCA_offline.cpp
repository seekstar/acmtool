//disjoint mustn't use merge by rank!!!!!!!
namespace LCA {
GRAPH g;
DISJOINT disj;
struct Q {
	int v, next, index;
} q[MAXQ << 1];
int m, head[MAXN], n, ans[MAXQ];
void Init(int _n) {
	m = 0;
	n = _n;
	memset(head, -1, (n+1) * sizeof(int));

	g.Init(n);
	disj.Init(n);
}
void AddQ_di(int u, int v, int i) {
	q[m] = Q{v, head[u], i};
	head[u] = m++;
}
void AddQ(int u, int v, int i) {
	AddQ_di(u, v, i);
	AddQ_di(v, u, i);
}
void dfs(int s, int f) {
	for (int v : g.s[s]) {
		if (f == v) continue;
		dfs(v, s);
		disj.Union(s, v);	//s becomes the father of v
	}
	for (int i = head[s]; ~i; i = q[i].next) {
		int v = q[i].v;
		if (disj.s[v] != -1) {	//has father
			ans[q[i].index] = disj.FindRoot(v);
		}
	}
}
void GetLca(int rt) {
	dfs(rt, -1);
}
}	//namespace LCA

//For directed graph
int GetRt(const GRAPH& g) {
	static bool isSon[MAXN];

	memset(isSon, 0, g.s.size() * sizeof(bool));
	for (auto e : g.s)
		for (int v : e)
			isSon[v] = true;
	int rt = 1;
	while (isSon[rt]) ++rt;
	return rt;
}

