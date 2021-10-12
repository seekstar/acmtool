struct Poly {
    s: Vec<UBigInt>,
}
impl Poly {
    fn new() -> Poly {
        Poly { s: Vec::new() }
    }
    // fn add_assign_with_shift(
    //     &mut self,
    //     rhs: &Poly,
    //     mut self_shift: usize,
    //     mut rhs_shift: usize,
    // ) {
    //     while self_shift < self.s.len() && rhs_shift < rhs.s.len() {
    //         self.s[self_shift] += &rhs.s[rhs_shift];
    //         self_shift += 1;
    //         rhs_shift += 1;
    //     }
    //     while rhs_shift < rhs.s.len() {
    //         self.s.push(rhs.s[rhs_shift].clone());
    //         rhs_shift += 1;
    //     }
    // }
    // Keep x^0 to x^n
    fn mul_truncate(&self, rhs: &Poly, n: usize) -> Poly {
        if self.s.is_empty() || rhs.s.is_empty() {
            return Poly::new();
        }
        assert!(self.s.len() <= n + 1);
        let mut ans = vec![UBigInt::new(); min(n + 1, self.s.len() + rhs.s.len() - 1)];
        for (i, v) in self.s.iter().enumerate() {
            for j in 0..min(rhs.s.len(), n + 1 - i) {
                ans[i + j] += &(v * &rhs.s[j]);
            }
        }
        Poly { s: ans }
    }
}

// impl Mul<&UBigInt> for &Poly {
//     type Output = Poly;
//     fn mul(self, rhs: &UBigInt) -> Poly {
//         let ans = Vec::with_capacity(self.s.len());
//         for v in &self.s {
//             ans.push(v * rhs);
//         }
//         Poly { s: ans }
//     }
// }

// impl MulAssign<&UBigInt> for Poly {
//     fn mul_assign(&mut self, rhs: &UBigInt) {
//         for v in &mut self.s {
//             *v *= rhs;
//         }
//     }
// }
