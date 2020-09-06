// Return -1 if not connected
fn kruskal<AnsT: Zero + NumCast + std::ops::AddAssign>(g: &Graph) -> Option<AnsT> {
//#[derive(PartialOrd)]
    #[derive(Copy, Clone, Eq, PartialEq)]
    struct Edge {
        d: i32,
        a: usize,
        b: usize
    }
    impl Ord for Edge {
        fn cmp(&self, rhs: &Edge) -> Ordering {
            rhs.d.cmp(&self.d)
        }
    }
    impl PartialOrd for Edge {
        fn partial_cmp(&self, rhs: &Edge) -> Option<Ordering> {
            Some(self.cmp(rhs))
        }
    }
    let mut disj = Disjoint::new(g.s.len());
    let mut pq = BinaryHeap::new();
    for (a, vec) in (&g.s).iter().enumerate() {
        for (b, d) in &*vec {
            pq.push(Edge{d: *d, a, b: *b});
        }
    }
    let n = g.s.len() - 1;
    let mut cnt = 0;
    let mut ans = AnsT::zero();
    while let Some(Edge{d, a, b}) = pq.pop() {
        if cnt == n - 1 {
            break;
        }
        let ra = disj.root_of(a);
        let rb = disj.root_of(b);
        if ra == rb {
            continue;
        }
        disj.union_root_neq(ra, rb);
        cnt += 1;
        ans += AnsT::from(d).unwrap();
    }
    if cnt == n - 1 {
        Some(ans)
    } else {
        None
    }
}
