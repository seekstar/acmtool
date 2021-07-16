macro_rules! define_mod_val {
    ($name:ident, $t:ty) => {
        #[derive(Copy, Clone)]
        struct $name<const P: $t> {
            v: $t
        }
        impl<const P: $t> From<$t> for $name<P> {
            fn from(v: $t) -> Self {
                Self { v }
            }
        }
        impl<const P: $t> Zero for $name<P> {
            fn zero() -> Self {
                Self { v: 0 }
            }
            fn is_zero(&self) -> bool {
                self.v == 0
            }
        }
        impl<const P: $t> std::ops::AddAssign<$t> for $name<P> {
            fn add_assign(&mut self, x: $t) {
                self.v += x; // Assumed not overflow here
                if self.v >= P {
                    self.v -= P;
                }
            }
        }
        impl<const P: $t> std::ops::AddAssign for $name<P> {
            fn add_assign(&mut self, x: Self) {
                *self += x.v;
            }
        }
        impl<const P: $t> std::ops::Add for $name<P> {
            type Output = Self;
            fn add(self, x: Self) -> Self {
                Self { v: self.v + x.v }
            }
        }
    };
    ($name:ident, $t:ty, $mul_t: ty) => {
        define_mod_val!($name, $t);
        impl<const P: $t> std::ops::Mul<$t> for $name<P> {
            type Output = Self;
            fn mul(self, x: $t) -> Self {
                Self::from((self.v as $mul_t * x as $mul_t % P as $mul_t) as $t)
            }
        }
        impl<const P: $t> std::ops::Mul for $name<P> {
            type Output = Self;
            fn mul(self, x: Self) -> Self {
                self * x.v
            }
        }
    };
}
define_mod_val!(ModValUsize, usize);
define_mod_val!(ModValI32, i32, i64);