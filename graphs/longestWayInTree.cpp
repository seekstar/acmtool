//Unweighted tree
int FarestVertex(const GRAPH& graph, int& u)
{
    queue<int>q1, q2;
    int cnt = 0;
    bool* vis = new bool[graph.m.size()];
    int v;
    int i;

    memset(vis, 0, graph.m.size() * sizeof(bool));
    q1.push(u);
    vis[u] = 1;
    while(!q1.empty())
    {
        while(!q1.empty())
        {
            u = q1.front();
            q1.pop();
            for(i = 0; i < (int)graph.m[u].size(); i++)
            {
                v = graph.m[u][i];
                if(!vis[v])
                {
                    vis[v] = 1;
                    q2.push(v);
                }
            }
        }
        cnt++;
        swap(q1, q2);
    }

    delete vis;
    return cnt-1;
}

int LongestWayTree(const GRAPH& graph)
{
    int i;

    for(i = 0; i < (int)graph.m.size() && graph.m[i].size() == 0; i++);

    if(i == (int)graph.m.size())
        return 0;
    FarestVertex(graph, i);
    return FarestVertex(graph, i);
}

//Weighted graph
DistType dist[MAXN];
DistType LongestPathInTree(const GRAPH& graph)
{
    VertexType i, u;
    DistType maxDist;

    DistInTree(graph, 1, dist); //1 is randomly chosen

    maxDist = -1;
    for(i = 1; i < (int)graph.s.size(); ++i)
    {
        if(maxDist < dist[i])
        {
            maxDist = dist[i];
            u = i;
        }
    }

    DistInTree(graph, u, dist);

    for(i = 1; i < (int)graph.s.size(); ++i)
    {
        maxDist = max(maxDist, dist[i]);
    }
    return maxDist;
}

template<typename VertexType, typename DistType>
void DistInTree(const GRAPH& graph, VertexType s, DistType dist[])
{
    queue<VertexType>q;
    VertexType v;

    memset(dist, -1, graph.s.size() * sizeof(DistType));
    dist[s] = 0;
    q.push(s);

    while(!q.empty())
    {
        s = q.front();
        q.pop();

        for(vector<pair<int, int> >::const_iterator it = graph.s[s].begin(); it != graph.s[s].end(); ++it)
        {
            v = it->first;
            if(dist[v] == -1)
            {
                dist[v] = dist[s] + it->second;
                q.push(v);
            }
        }
    }
}

