struct UBigInt {
    s: Vec<i32>
}
impl UBigInt {
    const BASE: i32 = 1000000000;
    const WIDTH: usize = 9;

    const fn new() -> UBigInt {
        UBigInt {
            s: Vec::new()
        }
    }
    fn from_string(str: &str) -> UBigInt {
        let mut s = Vec::new();
        let mut len = str.len();
        while len >= UBigInt::WIDTH {
            s.push(str[(len - UBigInt::WIDTH)..len].parse().unwrap());
            len -= UBigInt::WIDTH;
        }
        if len != 0 {
            s.push(str[0..len].parse().unwrap());
        }
        UBigInt {
            s
        }
    }
    fn clean(&mut self) -> &mut UBigInt {
        loop {
            let last = self.s.last();
            if let Some(c) = last {
                if *c != 0 {
                    break;
                }
                self.s.pop();
            } else {
                break;
            }
        }
        self
    }
    fn is_zero(&self) -> bool {
        return self.s.is_empty();
    }
    fn add_assign_with_shift(
        &mut self,
        rhs: &UBigInt,
        mut self_shift: usize,
        mut rhs_shift: usize,
    ) {
        let mut rem = 0;
        if self.s.len() < self_shift {
            self.s.resize(self_shift, 0);
        }
        while rhs_shift < rhs.s.len() || rem != 0 {
            if self_shift == self.s.len() {
                self.s.push(rem);
            } else {
                self.s[self_shift] += rem;
            }
            rem = 0;
            if rhs_shift < rhs.s.len() {
                self.s[self_shift] += rhs.s[rhs_shift];
            }
            if self.s[self_shift] >= Self::BASE {
                self.s[self_shift] -= Self::BASE;
                rem = 1;
            }
            self_shift += 1;
            rhs_shift += 1;
        }
    }
    fn div_assign_mod(&mut self, rhs: i32) -> i32 {
        assert!(rhs != 0);
        let mut rem = 0i64;
        for i in (0..self.s.len()).rev() {
            rem = rem * UBigInt::BASE as i64 + self.s[i] as i64;
            self.s[i] = (rem / rhs as i64) as i32;
            rem %= rhs as i64;
        }
        self.clean();
        rem as i32
    }
//     fn div_mod(&self, rhs: i32) -> (UBigInt, i32) {
//         assert!(rhs != 0);
//         let mut rem = 0i64;
//         let mut s = vec![0; self.s.len()];
//         for i in (0..self.s.len()).rev() {
//             rem = rem * UBigInt::BASE as i64 + self.s[i] as i64;
//             s[i] = (rem / rhs as i64) as i32;
//             rem %= rhs as i64;
//         }
//         (UBigInt{s}, rem as i32)
//     }
}

impl From<i32> for UBigInt {
    fn from(v: i32) -> UBigInt {
        assert!(v < Self::BASE);
        if v == 0 {
            UBigInt::new()
        } else {
            UBigInt { s: vec![v] }
        }
    }
}

impl AddAssign<i32> for UBigInt {
    fn add_assign(&mut self, mut rhs: i32) {
        assert!(0 <= rhs && rhs < UBigInt::BASE);
        let mut i = 0usize;
        while rhs != 0 {
            if i == self.s.len() {
                self.s.push(0);
            }
            self.s[i] += rhs;
            if self.s[i] > UBigInt::BASE {
                rhs = 1;
                self.s[i] -= UBigInt::BASE;
            } else {
                rhs = 0;
            }
            i += 1;
        }
    }
}

impl AddAssign<&UBigInt> for UBigInt {
    fn add_assign(&mut self, rhs: &UBigInt) {
        self.add_assign_with_shift(rhs, 0, 0);
    }
}

impl MulAssign<i32> for UBigInt {
    fn mul_assign(&mut self, rhs: i32) {
        assert!(0 <= rhs && rhs < Self::BASE);
        if rhs == 0 {
            self.s.clear();
            return;
        }
        let mut rem = 0;
        for v in &mut self.s {
            rem += *v as i64 * rhs as i64;
            *v = (rem % Self::BASE as i64) as i32;
            rem /= Self::BASE as i64;
        }
        if rem != 0 {
            self.s.push(rem as i32);
        }
    }
}
impl Mul<i32> for UBigInt {
    type Output = UBigInt;
    fn mul(mut self, rhs: i32) -> UBigInt {
        self *= rhs;
        self
    }
}
impl Mul<&UBigInt> for &UBigInt {
    type Output = UBigInt;
    fn mul(self, rhs: &UBigInt) -> UBigInt {
        let mut ans = UBigInt::new();
        for (i, v) in rhs.s.iter().enumerate() {
            ans.add_assign_with_shift(&(self.clone() * *v), i, 0);
        }
        ans
    }
}
impl MulAssign<&UBigInt> for UBigInt {
    fn mul_assign(&mut self, rhs: &UBigInt) {
        *self = &*self * rhs;
    }
}

impl Display for UBigInt {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        if self.s.is_empty() {
            return write!(f, "0");
        }
        write!(f, "{}", self.s[self.s.len() - 1])?;
        for i in (0..(self.s.len() - 1)).rev() {
            write!(f, "{:09}", self.s[i])?;
        }
        Ok(())
    }
}
