fn log2_ceil(n: usize) -> usize {
    let mut x = 1;
    let mut cnt = 0;
    while x < n {
        x <<= 1;
        cnt += 1;
    }
    return cnt;
}
fn log2_floor(n: usize) -> usize {
    let mut x = 1;
    let mut cnt = 0;
    while x <= n {
        x <<= 1;
        cnt += 1;
    }
    return cnt - 1;
}

struct RMQ<T> {
    s: Vec<Vec<T>>,
}
impl<T: std::default::Default + Copy + std::cmp::Ord> RMQ<T> {
    fn new(v: &Vec<T>) -> RMQ<T> {
        let logn = log2_floor(v.len()) + 1;
        let mut s = vec![vec![T::default(); logn]; v.len()];
        for i in 0..v.len() {
            s[i][0] = v[i];
        }
        for k in 1..logn {
            let step = 1 << (k - 1);
            for i in 0..(v.len() - step) {
                s[i][k] = cmp::min(s[i][k - 1], s[i + step][k - 1]);
            }
        }
        RMQ{s}
    }
    // The mx of [i, i + len), len != 0
    fn query(&self, i: usize, len: usize) -> T {
        if len == 1 {
            return self.s[i][0];
        }
        let k = log2_ceil(len) - 1;
        return cmp::min(self.s[i][k], self.s[i + len - (1 << k)][k]);
    }
}

