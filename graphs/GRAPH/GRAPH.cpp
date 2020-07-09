struct GRAPH {
	vector<vector<int> > s;
	void ClearEdges() {
		for (auto& i : s)
			i.resize(0);
	}
	void Init(int n) {
		s.resize(n+1);
		ClearEdges();
	}
	void AddUndi(int u, int v) {
		s[u].emplace_back(v);
		s[v].emplace_back(u);
	}
	void AddDi(int u, int v) {
		s[u].emplace_back(v);
	}
};