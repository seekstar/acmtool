//dinic for integer capacity
//O(n^2*m)
//O(min(n^(2/3),m^(1/2))*m) if all cap is 0 or 1
//O(sqrt(n)*m) in bipartite graph (äºŒåˆ†å›¾).Quicker than hungary
//support supper source point
struct EDGE {
    int to, next;
    cap_t cap;
};
struct DINIC {
    const static int max_edge = 12 * (MAXN * MAXM), max_node = 4 * MAXN * MAXM, INF = 0x3f3f3f3f;
    EDGE edge[max_edge];
    int n, m, head[max_node], depth[max_node], cur[max_node];

    void Init(int _n) {
        m = 0;
        n = _n + 1;
        memset(head, -1, n * sizeof(int));
    }
    void gAddDi(int u, int v, cap_t cap) {
        edge[m] = EDGE{v, head[u], cap};
        head[u] = m++;
    }

    void AddDi(int from, int to, cap_t cap) {
        gAddDi(from, to, cap);
        gAddDi(to, from, 0);
    }
    void AddUndi(int from, int to, cap_t cap) {
        gAddDi(from, to, cap);
        gAddDi(to, from, cap);
    }

    bool bfs(int s, int t) {
        queue<int> q;

        memset(depth, -1, n * sizeof(int));
        depth[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int e = head[u]; ~e; e = edge[e].next)
                if (edge[e].cap) {
                    int v = edge[e].to;
                    if (depth[v] == -1) {
                        depth[v] = depth[u] + 1;
                        if (v != t)
                            q.push(v);
                    }
                }
        }
        return (depth[t] != -1);
    }

    ans_t dfs(int s, int mi, int t) {
        ans_t ans = 0;
        if (s == t || 0 == mi)
            return mi;
        for (int &e = cur[s]; ~e; e = edge[e].next) {
            int v = edge[e].to, temp;
            if (depth[v] == depth[s] + 1 && (temp = dfs(v, min(mi, edge[e].cap), t))) {
                edge[e].cap -= temp;
                edge[1 ^ e].cap += temp;
                ans += temp;
                if (0 == (mi -= temp)) break;
            }
        }
        return ans;
    }

    ans_t solve(int s, int t) {
        ans_t ans = 0;
        while (bfs(s, t)) {
            for (int i = 0; i < n; ++i)
                cur[i] = head[i];
            ans += dfs(s, INF, t);
        }
        return ans;
    }
};

#if DEBUG
struct REC {
    int from, to, cap;
};
struct GetUsed {
    int caps[DINIC::max_edge];
    void Init(const DINIC& dinic) {
        for (int i = 0; i < dinic.m; ++i)
            caps[i] = dinic.edge[i].cap;
    }
    int get(REC ans[], const DINIC& dinic) const {
        int top = 0;
        for (int i = 0; i < dinic.n; ++i) {
            for (int e = dinic.head[i]; ~e; e = dinic.edge[e].next) {
                if (dinic.edge[e].cap < caps[e]) {
                    ans[top++] = {i, dinic.edge[e].to, caps[e] - dinic.edge[e].cap};
                }
            }
        }
        return top;
    }
};
#endif
