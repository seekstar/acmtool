//O(VE)
//record_e[i]是fa[i]->i的边的编号
template<typename dist_t>
void spfa(const GRAPH& g, int u, dist_t dist[]) {
    const static int maxn = MAXN;
    queue<int>q;
    static bool inq[maxn];
    memset(dist, 0x3f, g.s.size() * sizeof(dist_t));
    memset(inq, 0, g.s.size() * sizeof(bool));
    q.push(u);
    dist[u] = 0;
    while (!q.empty()) {
        u = q.front();
        q.pop();
        inq[u] = false;
        for (auto& e : g.s[u]) {
            int v = e.first;
            auto c = dist[u] + e.second;
            if (dist[v] > c) {
                dist[v] = c;
                if (!inq[v]) {
                    q.push(v);
                    inq[v] = true;
                }
            }
        }
    }
}
