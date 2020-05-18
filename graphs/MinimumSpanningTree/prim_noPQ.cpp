//Need Graph_matrix
template<typename DistType, int MAXN>
LL prim(const GRAPH<DistType, MAXN>& graph)
{
    LL ans = 0;
    int u = 1;
    static DistType dist[MAXN];
    static bool known[MAXN];
    int v;
    const int& n = graph.n;
    DistType minR;

    memset(known, 0, (n+1) * sizeof(bool));
    known[u] = 1;
    memset(dist, 0x3f, (n+1) * sizeof(int));
    dist[u] = 0;
    for(int cnt = 0; cnt < n-1; cnt++)
    {
        for(v = 1; v <= n; v++)//update
            if(!known[v] && dist[v] > graph.s[u][v])
                dist[v] = graph.s[u][v];
        minR = INF;
        for(v = 1; v <= n; v++)
            if(!known[v] && dist[v] < minR)
            {
                minR = dist[v];
                u = v;
            }
        if(minR != INF)
        {
            known[u] = 1;
            ans += minR;
        }
        else
            return -1;
    }
    return ans;
}
