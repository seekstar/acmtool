fn lowbit(x: usize) -> usize {
    return x & (-(x as isize) as usize);
}
struct Bit {
    s: Vec<i32>
}
impl Bit {
    fn new(mut v: Vec<i32>) -> Bit {
        for i in 1..v.len() {
            v[i] += v[i-1];
        }
        for i in (0..v.len()).rev() {
            v[i] -= v[i - lowbit(i)];
        }
        Bit{ s: v }
    }
    fn add(&mut self, mut i: usize, v: i32) {
        while i < self.s.len() {
            self.s[i] += v;
            i += lowbit(i);
        }
    }
    // The sum of [1, i]
    fn sum(&self, mut i: usize) -> i32 {
        let mut ans = 0;
        while i != 0 {
            ans += self.s[i];
            i -= lowbit(i);
        }
        return ans;
    }
}

