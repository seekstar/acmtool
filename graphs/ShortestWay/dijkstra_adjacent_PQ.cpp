template <typename T>
void dijkstra(const GRAPH& g, int s, T dist[]) {
    priority_queue<pair<T, int> >q;

    fill(dist, dist + g.s.size(), numeric_limits<T>::max());
    dist[s] = 0;
    q.push(make_pair(0, s));
    while (!q.empty()) {
        s = q.top().second;
        T c = -q.top().first;
        q.pop();
        if (c > dist[s]) continue;//old version
        for (auto i : g.s[s]) {
            int v = i.first;
            c = i.second;
            if (dist[v] > dist[s] + c) {
                dist[v] = dist[s] + c;
                q.push(make_pair(-dist[v], v));
            }
        }
    }
}
