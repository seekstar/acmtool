//mfmc. The version using SPFA. If you WA using the version of dijkstra, try this one.
//The inverse edge:	graph.AddEdge_di_quick(v, u, -cost, 0);
//Need spfa_GRAPH_EDGES
template<typename FlowType, typename CostType>
void mfmc(GRAPH_EDGES& graph, int s, int t, FlowType& maxFlow, CostType& minCost)
{
    static CostType dist[MAXN];
    static int record_e[MAXN];
    maxFlow = minCost = 0;
    while(1)
    {
        spfa(graph, s, dist, record_e);		//If all costs of edges are not negative, you can replace spfa with dijkstra.
        if(INF_CostType == dist[t])
            break;
        FlowType minF = INF_FlowType;
        for(int e = record_e[t]; e != -1; e = record_e[graph.edge[e].from])
            minF = min(minF, graph.edge[e].cap);
        maxFlow += minF;
        minCost += minF * dist[t];
        for(int e = record_e[t]; e != -1; e = record_e[graph.edge[e].from])
        {
            graph.edge[e].cap -= minF;
            graph.edge[1^e].cap += minF;
        }
    }
}
