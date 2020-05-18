//Need Graph_list
template<typename DistType>
void dijkstra(const GRAPH& graph, int s, DistType dist[], int fa[])
{
    static bool known[MAXN_DIJKSTRA];
    const int& n = graph.s.size();

    memset(dist, 0x3f, n*sizeof(dist[0]));
    memset(known, false, n * sizeof(known[0]));
    memset(fa, -1, n * sizeof(fa[0]));
    dist[s] = 0;
    for(int cnt = 0; cnt < n; ++cnt)
    {
        DistType minDist = INF;
        for(int i = 0; i < n; ++i){
            if(!known[i] && minDist > dist[i]){
                minDist = dist[i];
                s = i;
            }
        }
        known[s] = 1;
        for(auto e : graph.s[s]){
            int& v = e.first;
            DistType& cost = e.second;
            if(dist[v] > dist[s] + cost){
                dist[v] = dist[s] + cost;
                fa[v] = s;
            }
        }
    }
}