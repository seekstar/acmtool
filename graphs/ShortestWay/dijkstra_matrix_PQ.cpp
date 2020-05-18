template<typename VertexType, typename DistType>
void dijkstra(const GRAPH& graph, VertexType s, DistType dist[], int pre[])
{
    priority_queue<pair<DistType, VertexType> >q;
    int i;
    int u, cost;

    for(i = 0; i < graph.len; i++)
    {
        dist[i] = graph.inf;
        pre[i] = -1;
    }
    dist[s] = 0;
    q.push(make_pair(0, s));
    while(!q.empty())
    {
        u = q.top().second;
        cost = -q.top().first;
        q.pop();
        if(cost > dist[u])//�ɰ汾
            continue;
        for(i = 0; i < (int)graph.m[u].size(); i++)
        {
            if(graph.m[u][i] == graph.inf)
                continue;//û��·
            if(dist[i] > dist[u] + graph.m[u][i])
            {
                dist[i] = dist[u] + graph.m[u][i];
                q.push(make_pair(-dist[i], i));
                pre[i] = u;
            }
        }
    }
}
