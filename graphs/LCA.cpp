//Lowest Common Ancestors
//pure LCA
//Graph_weight_list
//depth[pre] = -1 for the pre of root
int depth[MAXN_LCA], fa[MAXN_LCA][LOG_MAXN_LCA];
void InitLca(int n) {
    memset(fa, 0, (n+1) * sizeof(fa[0]));
}
//Get the depth[s] according to depth[pre]
void InitLca_dfs(const GRAPH& g, int s, int pre) {
	//The depth of the root will be 0
    depth[s] = depth[pre] + 1;
    fa[s][0] = pre;
	for (int i = 1; i < LOG_MAXN_LCA; ++i)
        fa[s][i] = fa[fa[s][i-1]][i-1];
    for (int v : g.s[s]) {
        if (v == pre)
            continue;
        InitLca_dfs(g, v, s);
    }
}
void InitLca(const GRAPH& g, int rt, int pre) {
	depth[pre] = -1;
	InitLca_dfs(g, rt, pre);
}
int LCA(int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);
	for (int i = LOG_MAXN_LCA-1; i >= 0; --i)
		if (depth[fa[a][i]] >= depth[b])
			a = fa[a][i];
	if (a == b) return a;
    for (int i = LOG_MAXN_LCA-1; i >= 0; --i) 
        if (fa[a][i] != fa[b][i]) {
            a = fa[a][i];
            b = fa[b][i];
        }
    return fa[a][0];
}



//pure LCA. bfs. Can avoid stack overflow.
//Graph_weight_list
int depth[MAXN];
int fa[MAXN][MAX_LOG_N];
bool vis[MAXN];
void InitLca_bfs(const GRAPH& g, int s){
    static int q[MAXN];
    int qf = 0, qt = 0; //q_front, q_tail

    memset(vis, false, g.s.size() * sizeof(vis[0]));
    memset(fa, -1, g.s.size() * sizeof(fa[0]));
    q[qt++] = s;
    depth[s] = 0;
    vis[s] = true;
    while(qt > qf){
        int u = q[qf++];
        for(int i = 1; depth[u] >= (1 << i); ++i){
            fa[u][i] = fa[fa[u][i-1]][i-1];
        }
        for(auto e : g.s[u]){
            int v = e.first;
            if(!vis[v]){
                vis[v] = true;
                depth[v] = depth[u] + 1;
                fa[v][0] = u;
                q[qt++] = v;
            }
        }
    }
}



//Find the minimum weight of edge in the path from a to b
//Graph_weight_list
int depth[MAXN];
int fa[MAXN][MAX_LOG_N];
int lca_val[MAXN][MAX_LOG_N];	//The minimum weight of edges in the path from the node to its ancestor
bool vis[MAXN];
void InitLca(const GRAPH& g, int s){
    queue<int>q;

    q.push(s);
    depth[s] = 0;
    vis[s] = true;
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int i = 1; depth[u] >= (1 << i); ++i){
            fa[u][i] = fa[fa[u][i-1]][i-1];
            lca_val[u][i] = min(lca_val[u][i-1], lca_val[fa[u][i-1]][i-1]);
        }
        for(auto e : g.s[u]){
            int v = e.first;
            int w = e.second;
            if(!vis[v]){
                vis[v] = true;
                depth[v] = depth[u] + 1;
                fa[v][0] = u;
                lca_val[v][0] = w;
                q.push(v);
            }
        }
    }
}
void InitLca(const GRAPH& ng){
    memset(vis, false, ng.s.size() * sizeof(vis[0]));
    memset(fa, -1, ng.s.size() * sizeof(fa[0]));
    for(int i = 0; i < (int)ng.s.size(); ++i){
        if(!vis[i]){
            InitLca(ng, i);
        }
    }
}
//Find the minimum weight of edge in the path from a to b
int Lca(int a, int b){
    int ans = 0x3f3f3f3f;
    if(depth[a] < depth[b]){
        swap(a, b);
    }
    for(int i = 0, delta = depth[a] - depth[b]; delta; delta >>= 1, ++i)
        if(delta & 1) {
            ans = min(ans, lca_val[a][i]);
            a = fa[a][i];
        }
    for(int i = MAX_LOG_N - 1; i >= 0; --i){
        if(fa[a][i] != fa[b][i]){
            ans = min(ans, lca_val[a][i]);
            ans = min(ans, lca_val[b][i]);
            a = fa[a][i];
            b = fa[b][i];
        }
    }
    if(a != b){
        ans = min(ans, lca_val[a][0]);
        ans = min(ans, lca_val[b][0]);
    }
    return ans;
}









