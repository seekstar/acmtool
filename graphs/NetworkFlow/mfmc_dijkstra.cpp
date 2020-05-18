//mfmc. The version using dijkstra. If there are negative edges whose cap is not zero in the graph, use spfa at first.
//Need dijkstra_GRAPH_EDGES_PQ
//O(FE log(E)),F is the maximum flow
void AddDi_mfmc(GRAPH_EDGES& g, int u, int v, int cost, int cap) {
    g.AddDi(u, v, cost, cap);
    g.AddDi(v, u, -cost, 0);
}
template<typename FlowType, typename CostType>
void mfmc(GRAPH_EDGES& g, int s, int t, FlowType& maxFlow, CostType& minCost) {
	//const static int maxn = MAXN;
    static CostType dist[maxn];
    static int rec_e[maxn];
    maxFlow = minCost = 0;
    CostType realDist = 0;	//real distance from s to t

    while (1) {
        dijkstra(g, s, dist, rec_e);
        if (INF_CostType == dist[t])
            break;
        FlowType minF = numeric_limits<FlowType>::max();
        for (int e = rec_e[t]; ~e; e = rec_e[g.edge[e].from])
            minF = min(minF, g.edge[e].cap);
        maxFlow += minF;
        realDist += dist[t];
        minCost += minF * realDist;
        for (int e = rec_e[t]; ~e; e = rec_e[g.edge[e].from]) {
            g.edge[e].cap -= minF;
            g.edge[e^1].cap += minF;
        }
        for (int e = 0; e < g.m; ++e) {
            EDGE& edge = g.edge[e];
            edge.cost += dist[edge.from] - dist[edge.to];
        }
    }
}

