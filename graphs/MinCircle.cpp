//O(nE)
const int INF = 0x3f3f3f3f;
int MinCircle_bfs(const GRAPH& g, int s) {
    static int dist[MAXN], q[MAXN];
    int ql = 0, ans = INF;
    memset(dist, 0x3f, g.s.size() * sizeof(dist[0]));
    q[ql++] = s;
    dist[s] = 0;
    for (int i = 0; i < ql; ++i) {
        s = q[i];
        for (int v : g.s[s]) {
            if (dist[v] == INF) {
                dist[v] = dist[s] + 1;
                q[ql++] = v;
            } else if (dist[v] >= dist[s]) {    //dist[v] has been updated by other points
                ans = min(ans, dist[s] + dist[v] + 1);
            }
        }
    }
    return ans;
}
int MinCircle(const GRAPH& g) {
    int ans = INF;
    for (int i = 0; i < g.s.size(); ++i)
        ans = min(ans, MinCircle_bfs(g, i));
    return ans;
}
