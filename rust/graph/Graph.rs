// Not tested
struct Graph<T> {
    s: Vec<Vec<(usize, T)>>
}
impl Graph {
    fn new() -> Graph {
        Graph {
            s: Vec::new()
        }
    }
    fn clear_edges(&mut self) {
        for i in self.s.iter_mut() {
            i.clear();
        }
    }
    fn init(&mut self, n: usize) {
        self.s.resize(n + 1, Vec::new());
        self.clear_edges();
    }
    fn add_di(&mut self, u: usize, v: usize, dist: T) {
        self.s[u].push((v, dist));
    }
    fn add_undi(&mut self, u: usize, v: usize, dist: T) {
        self.add_di(u, v, dist);
        self.add_di(v, u, dist);
    }
}

struct GraphMat {
    s: Vec<Vec<i32>>
}
impl GraphMat {
    fn new(n: usize) -> GraphMat {
        GraphMat {
            s: vec![vec![0x3f3f3f3f; n + 1]; n + 1]
        }
    }
    fn add_di(&mut self, u: usize, v: usize, dist: i32) {
        self.s[u][v] = cmp::min(self.s[u][v], dist);    // In case of duplicate edges
    }
    fn add_undi(&mut self, u: usize, v: usize, dist: i32) {
        self.add_di(u, v, dist);
        self.add_di(v, u, dist);
    }
}
