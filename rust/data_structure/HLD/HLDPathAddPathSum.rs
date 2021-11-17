struct HLDPathAddPathSum<T> {
    base: HLDBase,
    sgt: SegTree<T>,
}
impl<T: Zero + Copy + std::ops::AddAssign + std::ops::Mul<Output = T> + From<usize> + std::ops::Add<Output = T>> HLDPathAddPathSum<T> {
    fn with_init_value(g: &Graph, rt: usize, v: &Vec<T>) -> Self {
        let base = HLDBase::new(g, rt);
        // base.ori[0] must be 0
        let nv = (0..v.len()).map(|i| v[base.ori[i]]).collect();
        Self {
            base,
            sgt: SegTree::with_init_value(&nv),
        }
    }
    fn path_sum(&mut self, mut x: usize, mut y: usize) -> T {
        let base = &self.base;
        let mut ans = T::zero();
        while base.top[x] != base.top[y] {
            if base.depth[base.top[x]] < base.depth[base.top[y]] {
                std::mem::swap(&mut x, &mut y);
            }
            ans += self.sgt.sum(1, 1, base.n, base.id[base.top[x]], base.id[x]);
            x = base.fa[base.top[x]];
        }
        if base.depth[x] > base.depth[y] {
            std::mem::swap(&mut x, &mut y);
        }
        ans + self.sgt.sum(1, 1, base.n, base.id[x], base.id[y])
    }
    fn path_add(&mut self, mut x: usize, mut y: usize, v: T) {
        let base = &self.base;
        while base.top[x] != base.top[y] {
            if base.depth[base.top[x]] < base.depth[base.top[y]] {
                std::mem::swap(&mut x, &mut y);
            }
            self.sgt.add(1, 1, base.n, base.id[base.top[x]], base.id[x], v);
            x = base.fa[base.top[x]];
        }
        if base.depth[x] > base.depth[y] {
            std::mem::swap(&mut x, &mut y);
        }
        self.sgt.add(1, 1, base.n, base.id[x], base.id[y], v);
    }
    fn subtree_sum(&mut self, x: usize) -> T {
        let base = &self.base;
        self.sgt.sum(1, 1, base.n, base.id[x], base.id[x] + base.siz[x] - 1)
    }
    fn subtree_add(&mut self, x: usize, v: T) {
        let base = &self.base;
        self.sgt.add(1, 1, base.n, base.id[x], base.id[x] + base.siz[x] - 1, v);
    }
}
