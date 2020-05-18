//Need Graph_list
int root[MAXN];
void shrink(GRAPH& ng, int n)
{
    int i, j;
    int u, v;

    ng.resize(n+1);
    StrongConnected();//root is modified
    for(i = 1; i <= n; i++)
    {
        u = root[i];
        for(j = 0; j < (int)g.m[i].size(); j++)
        {
            v = root[g.m[i][j]];
            if(u != v)
                ng.AddEdge_undi(u,v);
        }
    }
}

int dfn[MAXN];//ʱ���
int dfnc;
bool visited[MAXN];
bool inStack[MAXN];
int low[MAXN];
int pre[MAXN];
stack<int>s;
//modify root
void StrongConnected(void)
{
    int n = g.m.size();
    dfnc = 0;

    memset(visited, 0, n * sizeof(bool));
    memset(inStack, 0, n * sizeof(bool));
    for(int i = 1; i < n; i++)
        if(!visited[i])
        {
            pre[i] = 0;
            clear(s);//maybe needed.
            tarjan(i);
        }
}

void tarjan(int u)
{
    int i;
    int v;

    low[u] = dfn[u] = ++dfnc;
    s.push(u);
    inStack[u] = 1;

    for(i = 0; i < (int)g.m[u].size(); i++)
    {
        v = g.m[u][i];
        if(!visited[v])
        {
            visited[v] = 1;
            pre[v] = u;
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if(inStack[v] && v != pre[u])
            low[u] = min(low[u], dfn[v]);
    }
    if(dfn[u] == low[u])
        do
        {
            v = s.top();
            s.pop();
            inStack[v] = 0;
            root[v] = u;
        }
        while(u != v);
}
