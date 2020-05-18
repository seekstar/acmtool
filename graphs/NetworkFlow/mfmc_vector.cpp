struct EDGE {
    int from, to, inv;
    int cap, cost;
};
struct GRAPH {
    vector<vector<EDGE> > s;
    void Init(int n) {
        for (auto& i : s)
            i.resize(0);
        s.resize(n + 1);
    }
    void AddDi_mfmc(int u, int v, int cap, int cost) {  //  Èç¹ûÐèÒªÐÞžÄ costÎªLL
        s[u].push_back(EDGE{u, v, (int)s[v].size(), cap, cost});
        s[v].push_back(EDGE{v, u, (int)s[u].size() - 1, 0, -cost});
    }
};
//O(VE)
template<typename DT>
void spfa(GRAPH& g, int s, DT dist[], EDGE* rec[]) {
    queue<int> q;
    static bool inq[MAXN];

    memset(dist, 0x3f, g.s.size() * sizeof(DT));
    memset(inq, 0, g.s.size() * sizeof(bool));
    memset(rec, 0, g.s.size() * sizeof(int));
    dist[s] = 0;
    q.push(s);
    while (!q.empty()) {
        s = q.front();
        q.pop();
        inq[s] = false;
        for (auto& e : g.s[s]) {
            if (0 == e.cap)
                continue;
            if (dist[e.to] > dist[s] + e.cost) {
                dist[e.to] = dist[s] + e.cost;
                rec[e.to] = &e;
                if (!inq[e.to]) {
                    q.push(e.to);
                    inq[e.to] = true;
                }
            }
        }
    }
}

template<typename DT>
void dijkstra_pq(GRAPH& g, int s, DT dist[], EDGE* rec[]) {
    priority_queue<pair<DT, int> > q;//-dist, vertex

    memset(dist, 0x3f, g.s.size() * sizeof(DT));
    memset(rec, 0, g.s.size() * sizeof(int));
    dist[s] = 0;
    q.push(make_pair(0, s));
    while (!q.empty()) {
        s = q.top().second;
        DT c = -q.top().first;
        q.pop();
        if (c != dist[s]) continue;
        for (auto& e : g.s[s]) {
            if (0 == e.cap)
                continue;
            if (dist[e.to] > c + e.cost) {
                dist[e.to] = c + e.cost;
                rec[e.to] = &e;
                q.push(make_pair(-dist[e.to], e.to));
            }
        }
    }
}

//O(FE log(E)),F is the maximum flow
template<typename FT, typename CT>
void mfmc(GRAPH& g, int s, int t, FT &maxflow, CT &mincost) {
    CT inf;
    memset(&inf, 0x3f, sizeof(CT));
    static CT dist[MAXN];
    static EDGE* rec_e[MAXN];
    maxflow = mincost = 0;
    CT realdist = 0;    //real distance from s to t

    bool first = true;
    while (true) {
        if (first) {
            spfa(g, s, dist, rec_e);
            first = false;
        } else {
            dijkstra_pq(g, s, dist, rec_e);
        }
        if (inf == dist[t])
            break;
        FT minF = numeric_limits<FT>::max();
        for (auto e = rec_e[t]; e; e = rec_e[e->from])
            minF = min(minF, (FT)e->cap);
        maxflow += minF;
        realdist += dist[t];
        mincost += minF * realdist;
        for (auto e = rec_e[t]; e; e = rec_e[e->from]) {
            e->cap -= minF;
            g.s[e->to][e->inv].cap += minF;
        }
        for (auto& i : g.s)
            for (auto& e : i)
                e.cost += dist[e.from] - dist[e.to];
    }
}
