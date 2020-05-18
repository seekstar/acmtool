//Need GRAPH_EDGES
int f[MAX];//f[i] 为树中从i点到所有点的路径的权值的和
void GetTotalFlowOut(void)
{
    //memset(f, 0, (n+1)*sizeof(int));
    dfs1(1,0);
    dfs2(1,0);
}

void dfs1(int u, int fa)
{
    int v;
    for(int toe = g.head[u]; ~toe; toe = g.edge[toe].next)
    {
        v = g.edge[toe].to;
        if(v == fa)continue;
        dfs1(v, u);
        f[u] += f[v] + g.edge[toe].cap;
    }
}

void dfs2(int u, int fa)
{
    int v;
    for(int toe = g.head[u]; ~toe; toe = g.edge[toe].next)
    {
        v = g.edge[toe].to;
        if(v == fa)continue;
        f[v] = f[u] - g.edge[toe].cap + g.edge[1^toe].cap;
        dfs2(v, u);
    }
}
