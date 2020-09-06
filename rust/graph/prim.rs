// O(E + V^2)
// Return -1 if not connected
fn prim(g: &Graph) -> i32 {
    let n = g.s.len() - 1;
    let mut dist = vec![0x3f3f3f3f; g.s.len()];
    let mut known = vec![false; g.s.len()];
    let mut s = 1;  // randomly chosen
    let mut ans = 0;
    dist[s] = 0;
    known[s] = true;
    for _ in 1..n {
        for (v, d) in &g.s[s] {
            let v = *v;
            let d = *d;
            dist[v] = cmp::min(dist[v], d);
        }
        let mut mn = 0x3f3f3f3f;
        for (v, d) in (&dist).iter().enumerate() {
            let d = *d;
            if !known[v] && d < mn {
                mn = d;
                s = v;
            }
        }
        if mn == 0x3f3f3f3f {
            return -1;
        }
        known[s] = true;
        ans += mn;
    }
    return ans;
}

// O(V^2). Use matrix. In fact slower than the one using adjacency list.
// Return -1 if not connected
fn prim_mat(g: &GraphMat) -> i32 {
    const INF: i32 = 0x3f3f3f3f;
    let n = g.s.len() - 1;
    let mut dist = vec![INF; g.s.len()];
    let mut known = vec![false; g.s.len()];
    let mut s = 1;  // randomly chosen
    let mut ans = 0;
    known[s] = true;
    for _ in 1..n {
        for (v, d) in (&g.s[s]).iter().enumerate() {
            dist[v] = cmp::min(dist[v], *d);
        }
        let mut mn = INF;
        for (v, d) in (&dist).iter().enumerate() {
            let d = *d;
            if !known[v] && d < mn {
                mn = d;
                s = v;
            }
        }
        if mn == INF {
            return -1;
        }
        known[s] = true;
        ans += mn;
    }
    return ans;
}
