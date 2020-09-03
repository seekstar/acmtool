struct SegTree<T> {
    sum: Vec<T>
}
#[inline]
fn ls(rt: usize) -> usize {
    return rt << 1;
}
#[inline]
fn rs(rt: usize) -> usize {
    return rt << 1 | 1;
}
impl<T: Zero + Copy + std::default::Default + std::ops::AddAssign + std::clone::Clone> SegTree<T> {
    fn build(&mut self, rt: usize, l: usize, r: usize, v: &[T]) {
        if l == r {
            self.sum[rt] = v[r];
            return;
        }
        let mid = (l + r) >> 1;
        self.build(ls(rt), l, mid, v);
        self.build(rs(rt), mid + 1, r, v);
        self.sum[rt] = self.sum[ls(rt)] + self.sum[rs(rt)];
    }
    fn new(v: &[T]) -> SegTree<T> {
        let n = v.len() - 1;
        let mut sgt = SegTree { sum: vec![T::default(); 4 * n] };
        sgt.build(1, 1, n, v);
        return sgt;
    }
    fn add(&mut self, rt: usize, l: usize, r: usize, x: usize, v: T) {
        self.sum[rt] += v;
        if l == r {
            return;
        }
        let mid = (l + r) >> 1;
        if x <= mid {
            self.add(ls(rt), l, mid, x, v);
        } else {
            self.add(rs(rt), mid + 1, r, x, v);
        }
    }
    fn sum(&self, rt: usize, l: usize, r: usize, ll: usize, rr: usize) -> T {
        if ll <= l && r <= rr {
            return self.sum[rt];
        }
        let mid = (l + r) >> 1;
        let mut ans: T = T::zero();
        if mid >= ll {
            ans += self.sum(ls(rt), l, mid, ll, rr);
        }
        if mid < rr {
            ans += self.sum(rs(rt), mid + 1, r, ll, rr);
        }
        return ans;
    }
}

