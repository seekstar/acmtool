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
// Return -1 if not connected
// O(m log(m))
fn kruskal<AnsT: Zero + From<i32> + std::ops::AddAssign>(edges: Vec<Edge>, n: usize) -> Option<AnsT> {
    let mut pq = BinaryHeap::from(edges);
    let mut disj = Disjoint::new(n + 1);
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
        ans += AnsT::from(d);
    }
    if cnt == n - 1 {
        Some(ans)
    } else {
        None
    }
}


// A bit faster
#[derive(Copy, Clone, Eq, PartialEq)]
struct Edge {
    d: i32,
    a: usize,
    b: usize
}
impl Ord for Edge {
    fn cmp(&self, rhs: &Edge) -> Ordering {
        self.d.cmp(&rhs.d)
    }
}
impl PartialOrd for Edge {
    fn partial_cmp(&self, rhs: &Edge) -> Option<Ordering> {
        Some(self.cmp(rhs))
    }
}
// Return None if not connected
fn kruskal<AnsT: Zero + From<i32> + std::ops::AddAssign>(edges: &mut Vec<Edge>, n: usize) -> Option<AnsT> {
    edges.sort_unstable();
    let mut disj = Disjoint::new(n + 1);
    let mut cnt = 0;
    let mut ans = AnsT::zero();
    for Edge{d, a, b} in edges {
        if cnt == n - 1 {
            break;
        }
        let ra = disj.root_of(*a);
        let rb = disj.root_of(*b);
        if ra == rb {
            continue;
        }
        disj.union_root_neq(ra, rb);
        cnt += 1;
        ans += AnsT::from(*d);
    }
    if cnt == n - 1 {
        Some(ans)
    } else {
        None
    }
}
