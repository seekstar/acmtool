//O(VE)
//record_e[i]是fa[i]->i的边的编号
template<typename DistType>
void spfa(const GRAPH_EDGES& graph, int s, DistType dist[], int record_e[]) {
    queue<int>q;
    static bool inQueue[MAX_NODE_SPFA];

    memset(dist, 0x3f, graph.n * sizeof(DistType));
    memset(inQueue, 0, graph.n * sizeof(bool));
    memset(record_e, -1, graph.n * sizeof(int));
    q.push(s);
    dist[s] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inQueue[u] = 0;
        for (int e = graph.head[u]; ~e; e = graph.edge[e].next) {
            if (0 == graph.edge[e].cap) continue;
            int v = graph.edge[e].to;
            if (dist[v] > dist[u] + graph.edge[e].cost) {
                dist[v] = dist[u] + graph.edge[e].cost;
                record_e[v] = e;
                if (!inQueue[v]) {
                    q.push(v);
                    inQueue[v] = 1;
                }
            }
        }
    }
}


//O(VE)
//record_e[i]是fa[i]->i的边的编号
template<typename dist_t>
void spfa(const GRAPH_EDGES& g, int s, dist_t dist[], int rec_e[]) {
    const static int maxn = MAXN;
    queue<int>q;
    static bool inq[maxn];

    memset(dist, 0x3f, g.s.size() * sizeof(dist_t));
    memset(inq, 0, g.s.size() * sizeof(bool));
    memset(rec_e, -1, g.s.size() * sizeof(int));
    q.push(s);
    dist[s] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inq[u] = 0;
        for (int e = g.head[u]; ~e; e = g.edge[e].next) {
            if (0 == g.edge[e].cap) continue;
            int v = g.edge[e].to;
            if (dist[v] > dist[u] + g.edge[e].cost) {
                dist[v] = dist[u] + g.edge[e].cost;
                rec_e[v] = e;
                if (!inq[v]) {
                    q.push(v);
                    inq[v] = 1;
                }
            }
        }
    }
}
