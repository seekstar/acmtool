//Get the number of the simple paths on the tree whose length is k.
//Need GRAPH_weight_list
int k;
bool deleted[MAXN];

int maxp[MAXN]; //max part. The max size of the sub trees of i
int s[MAXN];    //size. The number of the vertexes in the tree whose root is u
void Init(int n)
{
    memset(deleted, 0, (n+1) * sizeof(bool));
}
//At first rt == u
void GetRoot(int& rt, int u, int fa, int sum)
{
    s[u] = 1;
    maxp[u] = 0;
    for(int i = 0; i < (int)g.s[u].size(); ++i)
    {
        int v = g.s[u][i].first;
        if(v == fa || deleted[v])continue;
        GetRoot(rt, v, u, sum);
        s[u] += s[v];
        maxp[u] = max(maxp[u], s[v]);
    }
    maxp[u] = max(maxp[u], sum - s[u]);
    if(maxp[u] < maxp[rt])rt = u;
}

void dfs_depth(int u, int fa, int sub_rt, int d, pair<int, int> arr[], int& len)
{
    arr[len++] = make_pair(d, sub_rt);
    for(int i = 0; i < (int)g.s[u].size(); ++i)
    {
        int v = g.s[u][i].first;
        if(deleted[v] || v == fa)continue;
        dfs_depth(v, u, sub_rt, d+g.s[u][i].second, arr, len);
    }
}

int PassRoot(int rt)
{
    static pair<int, int> arr[MAXN];  //first is depth, second is the root of the sub tree
    int len = 0;
    static int cnt[MAXN];    //cnt[i] is the number of the vertexes in the sub tree whose root is i in [L, R]

    int res = 0;

    arr[len++] = make_pair(0, rt);
    for(int i = 0; i < (int)g.s[rt].size(); ++i)
    {
        int v = g.s[rt][i].first;
        if(deleted[v])continue;
        dfs_depth(v, rt, v, g.s[rt][i].second, arr, len);
    }
    sort(arr, arr+len);
    for(int i = 0; i < len; ++i)
    {
        ++cnt[arr[i].second];
    }

    int L = 0, R = len-1;
    for(; L < R; ++L)
    {
        --cnt[arr[L].second];
        while(arr[L].first + arr[R].first > k && L < R)
        {
            --cnt[arr[R].second];
            --R;
        }
        res += R - L - cnt[arr[L].second];
    }
    cnt[arr[L].second] = 0;

    return res;
}

int solve(int u, int sum)
{
    int rt = 0;
    maxp[rt] = INT_MAX;
    GetRoot(rt, u, -1, sum);
    int ans = PassRoot(rt);

    deleted[rt] = 1;
    for(int i = 0; i < (int)g.s[rt].size(); ++i)
    {
        u = g.s[rt][i].first;
        if(deleted[u])continue;
        ans += solve(u, s[u]);
    }
    return ans;
}
