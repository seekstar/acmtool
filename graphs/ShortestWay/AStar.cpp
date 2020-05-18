//The lengths of the k shortest paths
//Warning, graph: first is weight, second is vertex
//O(ElgE+klog k)
template<typename T>
struct ASTAR_NODE{
    T g;    //h == 0
    int from, order;
    ASTAR_NODE(T _g, int _from, int _order) : g(_g), from(_from), order(_order) {}
    bool operator < (const ASTAR_NODE& rhs) const{
        return g > rhs.g;
    }
};
template<typename T>
void AStar(GRAPH& g, int s, int t, T ans[], int k){
    priority_queue<ASTAR_NODE<T> > pq;
    int cnt = 0;

    for (auto& i : g.s) {
        sort(i.begin(), i.end());
        for (int j = i.size() - 1; j > 0; --j)
            i[j].first -= i[j-1].first;   //diff
    }
    pq.emplace(g.s[s][0].first, s, 0);
    while(!pq.empty()) {
        auto g_u = pq.top().g;
        auto from = pq.top().from, order = pq.top().order;
        pq.pop();
        s = g.s[from][order].second;
        if (s == t && g_u) {
            ans[++cnt] = g_u;
            if (cnt == k) break;
        }

        if (++order < g.s[from].size())
            pq.emplace(g_u + g.s[from][order].first, from, order);
        if (!g.s[s].empty())
            pq.emplace(g_u + g.s[s][0].first, s, 0);
    }
}


