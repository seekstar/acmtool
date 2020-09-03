// In network flow, you should set s as the terminate node
// O(VE?)
// Do not know how to prove.
template <typename DistT>
int spfa_loop(const GRAPH_EDGES& g, int s, DistT dist[], int rec_e[]) {
	queue<pair<int, int> > q;
	static bool inq[g.max_node];
	memset(dist, 0x3f, g.n * sizeof(dist[0]));
	memset(inq, 0, g.n * sizeof(inq[0]));
	memset(rec_e, -1, g.n * sizeof(rec_e[0]));
	q.push(make_pair(s, 0));
	dist[s] = 0;
	while (!q.empty()) {
		int u = q.front().first;
		int cnt = q.front().second;
		q.pop();
		inq[u] = false;
		if (cnt >= g.n) {
			memset(inq, 0, g.n * sizeof(inq[0]));
			while (!inq[u]) {
				inq[u] = true;
				u = g.edge[rec_e[u]].from;
			};
			return u;
		}
		for (int e = g.head[u]; ~e; e = g.edge[e].next) {
			if (0 == g.edge[e].cap)
				continue;
			int v = g.edge[e].to;
			if (dist[v] > dist[u] + g.edge[e].cost) {
				dist[v] = dist[u] + g.edge[e].cost;
				rec_e[v] = e;
				if (!inq[v]) {
					q.push(make_pair(v, cnt + 1));
					inq[v] = true;
				}
			}
		}
	}
	return -1;
}

void use_neg_ring(GRAPH_EDGES &g, int u, const int rec_e[]) {
	int minF = 0x3f3f3f3f;
	int v = u;
	do {
		int e = rec_e[v];
		minF = min(minF, g.edge[e].cap);
		v = g.edge[e].from;
	} while (u != v);
	do {
		int e = rec_e[v];
		g.edge[e].cap -= minF;
		g.edge[e ^ 1].cap += minF;
		v = g.edge[e].from;
	} while (u != v);
}
