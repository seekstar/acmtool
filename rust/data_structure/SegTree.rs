#[inline]
fn ls(rt: usize) -> usize {
    return rt << 1;
}
#[inline]
fn rs(rt: usize) -> usize {
    return rt << 1 | 1;
}

// Point add, range sum
struct SegTree<T> {
    sum: Vec<T>
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


// Range add, range sum
struct SegTree<T> {
    sum: Vec<T>,
    lazy: Vec<T>
}
impl<T: Zero + Copy + std::ops::AddAssign + Clone + std::ops::Mul<Output = T> + From<usize> + std::ops::Add<Output = T>> SegTree<T> {
    fn with_init_value(v: &Vec<T>) -> Self {
        let n = v.len() - 1;
        let mut sgt = SegTree {
            sum: vec![T::zero(); n << 2],
            lazy: vec![T::zero(); n << 2]
        };
        sgt.build(1, 1, n, v);
        return sgt;
    }
    fn build(&mut self, rt: usize, l: usize, r: usize, v: &Vec<T>) {
        if l == r {
            self.sum[rt] = v[r];
            return;
        }
        let mid = (l + r) >> 1;
        self.build(ls(rt), l, mid, v);
        self.build(rs(rt), mid + 1, r, v);
        self.push_up(rt);
    }
    fn push_up(&mut self, rt: usize) {
        self.sum[rt] = self.sum[ls(rt)] + self.sum[rs(rt)];
    }
    fn push_down(&mut self, rt: usize, l: usize, mid: usize, r: usize) {
        let lazy = self.lazy[rt];
        if !lazy.is_zero() {
            self.sum[ls(rt)] += lazy * (mid - l + 1).into();
            self.lazy[ls(rt)] += lazy;
            self.sum[rs(rt)] += lazy * (r - mid).into();
            self.lazy[rs(rt)] += lazy;
            self.lazy[rt] = T::zero();
        }
    }
    fn add(&mut self, rt: usize, l: usize, r: usize, ll: usize, rr: usize, v: T) {
        if ll <= l && r <= rr {
            self.sum[rt] += v * (r - l + 1).into();
            if l != r {
                self.lazy[rt] += v;
            }
            return;
        }
        let mid = (l + r) >> 1;
        self.push_down(rt, l, mid, r);
        if ll <= mid {
            self.add(ls(rt), l, mid, ll, rr, v);
        }
        if mid < rr {
            self.add(rs(rt), mid + 1, r, ll, rr, v);
        }
        self.push_up(rt);
    }
    fn sum(&mut self, rt: usize, l: usize, r: usize, ll: usize, rr: usize) -> T {
        if ll <= l && r <= rr {
            return self.sum[rt];
        }
        let mid = (l + r) >> 1;
        self.push_down(rt, l, mid, r);
        let mut ans = T::zero();
        if ll <= mid {
            ans = self.sum(ls(rt), l, mid, ll, rr);
        }
        if mid < rr {
            ans += self.sum(rs(rt), mid + 1, r, ll, rr);
        }
        ans
    }
}


// Range add, range mul, range sum
type T = i32;
type MulT = i64;
struct SegTree {
    p: T,
    sum: Vec<T>,
    lazy_mul: Vec<T>,
    lazy_add: Vec<T>
}
impl SegTree {
    fn new(p: T, v: &Vec<T>) -> SegTree {
        let n = v.len() - 1;
        let mut sgt = SegTree {
            p,
            sum: vec![T::default(); n << 2],
            lazy_mul: vec![T::one(); n << 2],
            lazy_add: vec![T::zero(); n << 2]
        };
        sgt.build(1, 1, n, v);
        return sgt;
    }
    fn build(&mut self, rt: usize, l: usize, r: usize, v: &Vec<T>) {
        if l == r {
            self.sum[rt] = v[r];
            return;
        }
        let mid = (l + r) >> 1;
        self.build(ls(rt), l, mid, v);
        self.build(rs(rt), mid + 1, r, v);
        self.push_up(rt);
    }
    fn push_up(&mut self, rt: usize) {
        self.sum[rt] = (self.sum[ls(rt)] + self.sum[rs(rt)]) % self.p;
    }
    fn push_down(&mut self, rt: usize, l: usize, mid: usize, r: usize) {
        if self.lazy_mul[rt] != T::one() {
            self.sum[ls(rt)] = (self.sum[ls(rt)] as MulT * self.lazy_mul[rt] as MulT % self.p as MulT) as T;
            self.lazy_mul[ls(rt)] = (self.lazy_mul[ls(rt)] as MulT * self.lazy_mul[rt] as MulT % self.p as MulT) as T;
            self.lazy_add[ls(rt)] = (self.lazy_add[ls(rt)] as MulT * self.lazy_mul[rt] as MulT % self.p as MulT) as T;
            self.sum[rs(rt)] = (self.sum[rs(rt)] as MulT * self.lazy_mul[rt] as MulT % self.p as MulT) as T;
            self.lazy_mul[rs(rt)] = (self.lazy_mul[rs(rt)] as MulT * self.lazy_mul[rt] as MulT % self.p as MulT) as T;
            self.lazy_add[rs(rt)] = (self.lazy_add[rs(rt)] as MulT * self.lazy_mul[rt] as MulT % self.p as MulT) as T;
            self.lazy_mul[rt] = T::one();
        }
        if self.lazy_add[rt] != T::zero() {
            self.sum[ls(rt)] = ((self.sum[ls(rt)] as MulT + self.lazy_add[rt] as MulT * (mid - l + 1) as MulT) % self.p as MulT) as T;
            self.lazy_add[ls(rt)] = (self.lazy_add[ls(rt)] + self.lazy_add[rt]) % self.p;
            self.sum[rs(rt)] = ((self.sum[rs(rt)] as MulT + self.lazy_add[rt] as MulT * (r - mid) as MulT) % self.p as MulT) as T;
            self.lazy_add[rs(rt)] = (self.lazy_add[rs(rt)] + self.lazy_add[rt]) % self.p;
            self.lazy_add[rt] = T::zero();
        }
    }
    fn add(&mut self, rt: usize, l: usize, r: usize, ll: usize, rr: usize, v: T) {
        if ll <= l && r <= rr {
            self.sum[rt] = ((self.sum[rt] as MulT + v as MulT * (r - l + 1) as MulT) % self.p as MulT) as T;
            if l != r {
                self.lazy_add[rt] = (self.lazy_add[rt] + v) % self.p;
            }
            return;
        }
        let mid = (l + r) >> 1;
        self.push_down(rt, l, mid, r);
        if ll <= mid {
            self.add(ls(rt), l, mid, ll, rr, v);
        }
        if mid < rr {
            self.add(rs(rt), mid + 1, r, ll, rr, v);
        }
        self.push_up(rt);
    }
    fn mul(&mut self, rt: usize, l: usize, r: usize, ll: usize, rr: usize, v: T) {
        if ll <= l && r <= rr {
            self.sum[rt] = (self.sum[rt] as MulT * v as MulT % self.p as MulT) as T;
            if l != r {
                self.lazy_mul[rt] = (self.lazy_mul[rt] as MulT * v as MulT % self.p as MulT) as T;
                self.lazy_add[rt] = (self.lazy_add[rt] as MulT * v as MulT % self.p as MulT) as T;
            }
            return;
        }
        let mid = (l + r) >> 1;
        self.push_down(rt, l, mid, r);
        if ll <= mid {
            self.mul(ls(rt), l, mid, ll, rr, v);
        }
        if mid < rr {
            self.mul(rs(rt), mid + 1, r, ll, rr, v);
        }
        self.push_up(rt);
    }
    fn sum(&mut self, rt: usize, l: usize, r: usize, ll: usize, rr: usize) -> T {
        if ll <= l && r <= rr {
            return self.sum[rt];
        }
        let mid = (l + r) >> 1;
        self.push_down(rt, l, mid, r);
        let mut ans = T::zero();
        if ll <= mid {
            ans = self.sum(ls(rt), l, mid, ll, rr);
        }
        if mid < rr {
            ans = (ans + self.sum(rs(rt), mid + 1, r, ll, rr)) % self.p;
        }
        return ans;
    }
}
