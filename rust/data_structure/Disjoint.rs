struct Disjoint {
    s: Vec<usize>
}
impl Disjoint {
    fn new(n: usize) -> Disjoint {
        Disjoint {
            s: vec![0; n + 1]
        }
    }
    fn root_of(&mut self, mut a: usize) -> usize {
        let mut b = a;
        while self.s[a] != 0 {
            a = self.s[a];
        }
        while self.s[b] != 0 {
            let fa = self.s[b];
            self.s[b] = a;
            b = fa;
        }
        a
    }
    fn union_root_neq(&mut self, a: usize, b: usize) {
        self.s[a] = b;
    }
    fn union_root(&mut self, a: usize, b: usize) {
        if a != b {
            self.union_root_neq(a, b);
        }
    }
    fn union(&mut self, a: usize, b: usize) {
        let ra = self.root_of(a);
        let rb = self.root_of(b);
        self.union_root(ra, rb);
    }
}


struct Disjoint {
    s: Vec<isize>
}
impl Disjoint {
    fn new(n: usize) -> Disjoint {
        Disjoint {
            s: vec![-1; n + 1]
        }
    }
    fn root_of(&mut self, a: usize) -> usize {
        if self.s[a] < 0 {
            a
        } else {
            self.s[a] = self.root_of(self.s[a] as usize) as isize;
            self.s[a] as usize
        }
    }
    fn union_root_neq(&mut self, a: usize, b: usize) {
        if self.s[a] < self.s[b] {
            self.s[a] += self.s[b];
            self.s[b] = a as isize;
        } else {
            self.s[b] += self.s[a];
            self.s[a] = b as isize;
        }
    }
    fn union_root(&mut self, a: usize, b: usize) {
        if a != b {
            self.union_root_neq(a, b);
        }
    }
    fn union(&mut self, a: usize, b: usize) {
        let ra = self.root_of(a);
        let rb = self.root_of(b);
        self.union_root(ra, rb);
    }
}
