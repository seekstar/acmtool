struct Graph {
	vector<vector<pair<int, int> > > s;
	void clear_edges() {
		for (auto& i : s) {
			i.resize(0);
		}
	}
	void init(int n) {
		clear_edges();
		s.resize(n + 1);
	}
	void add_di(int u, int v, int dist) {
		s[u].emplace_back(v, dist);
	}
	void add_undi(int u, int v, int dist) {
		s[u].emplace_back(v, dist);
		s[v].emplace_back(u, dist);
	}
};
