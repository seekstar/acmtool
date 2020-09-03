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
struct Graph {
	vector<vector<pair<int, int> > > s;
	void clear_edges() {
		for (auto& i : s) {
			i.resize(0);
		}
	}
	void init(int n) {
		clear_edges();
		s.resize(n);
	}
	void add_di(int u, int v, int dist) {
		s[u].emplace_back(v, dist);
	}
};
