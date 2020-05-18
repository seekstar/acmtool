//Need Graph_list
int root[MAXN];	//root[i] is the root of the strong connectivity where point i is.
//des[i] == 1 means i is a destination.
void shrink(GRAPH& ng, int n, bool des[], int& s)
{
    int i, j;
    int u,v;

    ng.resize(n+1);
    fill(ng.c.begin(), ng.c.end(), 0);
    StrongConnected();//root is modified
    for(i = 1; i <= n; i++)
    {
        u = root[i];
        ng.c[u] += g.c[i];			//Modify cost
        for(j = 0; j < (int)g.m[i].size(); j++)
        {
            v = root[g.m[i][j]];
            if(u != v)
                ng.AddEdge_di(u,v);
        }
    }
    for(i = 1; i <= n; i++)
        if(des[i] && !des[root[i]])
        {
            des[root[i]] = 1;
            des[i] = 0;
        }
    s = root[s];
}

int dfn[MAXN];	//time stamp of depth first search
int dfnc;
bool visited[MAXN];
bool inStack[MAXN];
int low[MAXN];
stack<int>s;
void StrongConnected(void)
{
    int n = g.m.size();
    dfnc = 0;

    memset(visited, 0, n * sizeof(bool));
    memset(inStack, 0, n * sizeof(bool));
    for(int i = 1; i < n; i++)
        if(!visited[i])
        {
            clear(s);
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
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if(inStack[v])
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
