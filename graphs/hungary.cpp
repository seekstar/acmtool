//O(VE)
int pair1[MAX1][MAX2];//pair1[0] is invalid. pair1[i][j] == k means that k(in the second group) can be distributed to i(in the first group)
int len1[MAX1];
int match2[MAX2];//match2[i] == j means that i(in the second group) is distributed to the j(in the first group)
bool vis2[MAX2];
//n1 is the size of the first group
void Init(int n1, int n2) {
    memset(len1, 0, (n1+1) * sizeof(int));
    memset(match2, 0, (n2+1) * sizeof(int));
}
void AddPair(int u, int v) {
    pair1[u][len1[u]++] = v;
}
//If succeed return 1,else return 0
bool dfs_hungary(int x) {
    for(int i = 0; i < len1[x]; i++) {
        int right = pair1[x][i];
        if(!vis2[right]) {
            vis2[right] = 1;
            if(match2[right] == 0 || dfs_hungary(match2[right])) {
                match2[right] = x;
                return 1;
            }
        }
    }
    return 0;
}
int hungary(int n1, int n2) {
    int tot = 0;
    for(int i = 1; i <= n1; i++) {	//If i=n1;i;--i, then the final pairs' lexicographical order will be the least
        memset(vis2, 0, (n2+1) * sizeof(bool));
        if(dfs_hungary(i))
            ++tot;
    }
    return tot;
}





bool left[MAXN], vis[MAXN];
int match[MAXN];
//If succeed return 1,else return 0
bool dfs_hungary(const GRAPH& g, int u) {
    for (int v : g.s[u]) {
        if (!vis[v]) {
            vis[v] = true;
            if (!match[v] || dfs_hungary(g, match[v])) {
                match[v] = u;
                return true;
            }
        }
    }
    return false;
}
int hungary(const GRAPH& g) {
    int ans = 0, n = g.s.size();
    memset(match, 0, n * sizeof(int));
    for (int i = 1; i < n; ++i) {
        if (left[i]) {
            memset(vis, 0, n * sizeof(vis[0]));
            if (dfs_hungary(g, i)) ++ans;
        }
    }
    return ans;
}

void dfs_color(const GRAPH& g, int u, bool c) {
    left[u] = c;
    vis[u] = true;
    for (int v : g.s[u])
        if (!vis[v])
            dfs_color(g, v, !c);
}
int Solve(const GRAPH& g) {
    memset(vis, 0, g.s.size() * sizeof(vis[0]));
    for (int i = 1; i < (int)g.s.size(); ++i)
        if (!vis[i])
            dfs_color(g, i, false);
    return hungary(g);
}

void dfs_independent(int ans[], int& len, const GRAPH& g, int u) {
	if (vis[u]) return;
	vis[u] = true;
	for (int v : g.s[u]) {
		if (!vis[v]) {
			vis[v] = true;
			dfs_independent(ans, len, g, match[v]);
		}
	}
}
//O(n+m)
void Independent(int ans[], int& len, const GRAPH& g) {
    Solve(g);
    static bool paired[MAXN];
    int n = g.s.size();
    memset(vis, 0, n * sizeof(vis[0]));
    memset(paired, 0, n * sizeof(paired[0]));
    for (int i = 1; i < n; ++i)       //start from 1
        if (match[i])
            paired[match[i]] = true;
    for (int i = 1; i < n; ++i)
        if (left[i] && !paired[i])
            dfs_independent(ans, len, g, i);
    for (int i = 1; i < n; ++i)
        if ((!vis[i] && !left[i]) || (vis[i] && left[i]))
            ans[len++] = i;
}





//Don't need to dfs_color
bool vis[MAXN];
int match[MAXN];
//If succeed return 1,else return 0
bool dfs_hungary(const GRAPH& g, int u) {
    for (int v : g.s[u]) {
        if (!vis[v]) {
            vis[v] = true;
            if (!match[v] || dfs_hungary(g, match[v])) {
                match[v] = u;
                match[u] = v;
                return true;
            }
        }
    }
    return false;
}
int hungary(const GRAPH& g) {
    int ans = 0, n = g.s.size();
    memset(match, 0, n * sizeof(int));
    for (int i = 1; i < n; ++i) {
        if (!match[i]) {
            memset(vis, 0, n * sizeof(vis[0]));
            if (dfs_hungary(g, i)) ++ans;
        }
    }
    return ans;
}

