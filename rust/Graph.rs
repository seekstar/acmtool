// Not tested
struct Graph {
    s: Vec<Vec<(usize, i32)>>
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
//     fn add_undi(&mut self, u: usize, v: usize) {
//         self.s[u].push(v);
//         self.s[v].push(u);
//     }
    fn add_di(&mut self, u: usize, v: usize, dist: i32) {
        self.s[u].push((v, dist));
    }
    fn add_undi(&mut self, u: usize, v: usize, dist: i32) {
        self.add_di(u, v, dist);
        self.add_di(v, u, dist);
    }
}

