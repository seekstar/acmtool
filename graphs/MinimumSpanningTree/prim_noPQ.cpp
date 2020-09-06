// O(E + V^2)
template <typename AnsT>
int prim(const Graph& g) {
	const int INF = 0x3f3f3f3f;
    const int& n = g.s.size() - 1;
    static int dist[MAXN];
    static bool known[MAXN];
    AnsT ans = 0;
    int u = 1;	// Randomly chosen

    memset(known, 0, (n+1) * sizeof(bool));
    known[u] = 1;
    memset(dist, 0x3f, (n+1) * sizeof(int));
    dist[u] = 0;
    for(int _ = 0; _ < n - 1; ++_) {
		for (auto &vd : g.s[u]) {
			int v = vd.first, d = vd.second;
			if (!known[v] && dist[v] > d) {
				dist[v] = d;
			}
		}
        int minR = INF;
        for(int v = 1; v <= n; ++v) {
            if(!known[v] && dist[v] < minR) {
                minR = dist[v];
                u = v;
            }
		}
		if (minR == INF)
			return -1;
		known[u] = true;
		ans += minR;
    }
    return ans;
}
