//adjacent graph
LL Kruskal(const GRAPH& g, GRAPH& ng) {
	typedef pair<int, pair<int, int> > pipii;
	priority_queue<pipii, vector<pipii>, greater<pipii> > pq;
	static DISJOINT disj;
	int n = g.s.size() - 1;

	ng.Init(n);
	disj.Init(n);
	for (int i = 1; i <= n; ++i) {
		for (size_t j = 0; j < g.s[i].size(); ++j) {
			pq.push(make_pair(g.s[i][j].second, make_pair(i, g.s[i][j].first)));
		}
	}
	LL ans = 0;
	for (int cnt = 1; cnt < n; ++cnt) {
		int u, v, c;
		do {
			if (pq.empty()) return -1;
			auto now = pq.top();
			pq.pop();
			u = now.second.first;
			v = now.second.second;
			c = now.first;
		} while (disj.FindRoot(u) == disj.FindRoot(v));
		disj.Union(u, v);
		ans += c;
		ng.AddUndi(u, v, c);
	}
	return ans;
}

