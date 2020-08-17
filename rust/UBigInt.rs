struct UBigInt {
    s: Vec<i32>
}
impl UBigInt {
    const BASE: i32 = 1000000000;
    const WIDTH: usize = 9;

//     const fn new() -> UBigInt {
//         UBigInt {
//             s: Vec::new()
//         }
//     }
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
    fn diveq_mod(&mut self, rhs: i32) -> i32 {
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
impl ops::AddAssign<i32> for UBigInt {
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

