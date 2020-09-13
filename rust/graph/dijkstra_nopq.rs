fn dijkstra(g: &Graph, mut s: usize) -> Vec<i32> {
    const INF: i32 = 0x3f3f3f3f;
    let mut dist = vec![INF; g.s.len()];
    let mut known = vec![false; g.s.len()];
    dist[s] = 0;
    for _i in 0..(g.s.len()) {
        let mut mn = INF;
        for i in 0..(g.s.len()) {
            if !known[i] && mn > dist[i] {
                mn = dist[i];
                s = i;
            }
        }
        known[s] = true;
        for (v, d) in &g.s[s] {
            let v = *v;
            let d = *d;
            dist[v] = cmp::min(dist[v], mn + d);
        }
    }
    return dist;
}

