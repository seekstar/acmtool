struct HLDBase {
    n: usize,
    fa: Vec<usize>,
    depth: Vec<usize>,
    siz: Vec<usize>,
    id: Vec<usize>,
    top: Vec<usize>,
    ori: Vec<usize>,
}
impl HLDBase {
    fn dfs1(&mut self, g: &Graph, son: &mut Vec<usize>, s: usize, f: usize, d: usize) {
        self.depth[s] = d;
        self.fa[s] = f;
        self.siz[s] = 1;
        for v in &g.s[s] {
            let v = *v;
            if v == f {
                continue;
            }
            self.dfs1(g, son, v, s, d + 1);
            self.siz[s] += self.siz[v];
            if self.siz[v] > self.siz[son[s]] {
                son[s] = v;
            }
        }
    }
    //t is the top of the current list
    fn dfs2(&mut self, g: &Graph, son: &Vec<usize>, tot: &mut usize, s: usize, t: usize) {
        self.top[s] = t;
        *tot += 1;
        self.id[s] = *tot;
        self.ori[*tot] = s;
        if son[s] == 0 {
            return;
        }
        self.dfs2(g, son, tot, son[s], t);
        for v in &g.s[s] {
            let v = *v;
            if v != son[s] && v != self.fa[s] {
                self.dfs2(g, son, tot, v, v);
            }
        }
    }
    fn new(g: &Graph, rt: usize) -> Self {
        let n = g.s.len() - 1;
        let mut tot = 0;
        let mut son = vec![0; n+1];
        // Actually no need to be 0
        let mut hld = Self {
            n,
            fa: vec![0; n+1],
            depth: vec![0; n+1],
            siz: vec![0; n+1],
            id: vec![0; n+1],
            top: vec![0; n+1],
            ori: vec![0; n+1],
        };
        hld.dfs1(g, &mut son, rt, 0, 1);
        hld.dfs2(g, &son, &mut tot, rt, rt);
        hld
    }
}
