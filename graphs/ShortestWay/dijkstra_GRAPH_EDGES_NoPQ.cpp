//O(n^2)
//rec_e[i]是fa[i]->i的边的编号
template<typename dist_t>
void dijkstra(const GRAPH_EDGES& g, int s, dist_t dist[], int rec_e[]) {
	const static int maxn = MAXN;
    static bool known[maxn];
    const int& n = g.n;

    memset(dist, 0x3f, n * sizeof(dist_t));
    memset(rec_e, -1, n * sizeof(int));
    memset(known, 0, n * sizeof(bool));
    dist[s] = 0;
    for (int cnt = 0; cnt < n; ++cnt) {
        auto minDist = numeric_limits<dist_t>::max();
        for (int i = 0; i < n; ++i) {
            if (!known[i] && minDist > dist[i]) {
                minDist = dist[i];
                s = i;
            }
        }
        known[s] = true;
        for (int e = g.head[s]; ~e; e = g.edge[e].next) {
            if (0 == g.edge[e].cap) continue;
            int v = g.edge[e].to;
            if (dist[v] > dist[s] + g.edge[e].cost) {
                dist[v] = dist[s] + g.edge[e].cost;
                rec_e[v] = e;
            }
        }
    }
}

