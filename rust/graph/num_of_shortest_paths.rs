// dist is from s
// dist[i] > 0
fn num_of_shortest_paths(g: &Graph, dist: &Vec<i32>, s: usize, t: usize) -> u64 {
    // Reverse
    fn dfs(g: &Graph, dist: &Vec<i32>, s: usize, cur: usize) -> u64 {
        if cur == s {
            return 1;
        }
        let mut cnt = 0u64;
        for (v, d) in &g.s[cur] {
            let v = *v;
            let d = *d;
            if dist[v] + d == dist[cur] {
                cnt += dfs(&g, &dist, s, v);
            }
        }
        return cnt;
    };
    return dfs(&g, &dist, s, t);
}
