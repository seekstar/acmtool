//O(ElgE)
//record_e[i]��fa[i]->i�ıߵı��
template<typename DistType>
void dijkstra(const GRAPH_EDGES& g, int s, DistType dist[], int rec_e[]) {
    const int& n = g.n;
    priority_queue<pair<DistType, int> > pq;	//-dist, vertex

    memset(dist, 0x3f, n * sizeof(DistType));
    memset(rec_e, -1, n * sizeof(int));
    dist[s] = 0;
    pq.push(make_pair(0, s));
    while (!pq.empty()) {
        s = pq.top().second;
        DistType c = -pq.top().first;
        pq.pop();
        if (c != dist[s]) continue;
        for (int e = g.head[s]; ~e; e = g.edge[e].next) {
            if (0 == g.edge[e].cap) continue;
            int v = g.edge[e].to;
            if (dist[v] > c + g.edge[e].cost) {
                dist[v] = c + g.edge[e].cost;
                rec_e[v] = e;
                pq.push(make_pair(-dist[v], v));
            }
        }
    }
}

