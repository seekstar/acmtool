const int INF = 0x3f3f3f3f;
template<typename DistType, int MAXN>
struct GRAPH
{
    DistType s[MAXN][MAXN];     //[0, n]
    int n;

    void Init(int _n)//Init(n+1),if your points are numbered from 1 to n
    {
        n = _n;
        for(int i = 0; i <= n; i++)
            for(int j = 0; j <= n; j++)
                s[i][j] = INF;
    }
    void AddEdge_di(int u, int v, int w)
    {
        if(s[u][v] > w)
            s[u][v] = w;
    }
    void AddEdge_undi(int u, int v, int w)
    {
        AddEdge_di(u, v, w);
        AddEdge_di(v, u, w);
    }
};
