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
        impl<const P: $t> std::ops::AddAssign<$t> for $name<P> {
            fn add_assign(&mut self, x: $t) {
                self.v += x; // Assumed not overflow here
                if self.v >= P {
                    self.v -= P;
                }
            }
        }
        impl<const P: $t> std::ops::Add<$t> for $name<P> {
            type Output = Self;
            fn add(mut self, x: $t) -> Self {
                self += x;
                self
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
                self + x.v
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


// Unsafe for multithread
macro_rules! define_mod_val_static {
    ($name:ident, $t:ty, $p:ident) => {
        #[derive(Copy, Clone)]
        struct $name {
            v: $t
        }
        impl From<$t> for $name {
            fn from(v: $t) -> Self {
                Self { v }
            }
        }
        impl std::ops::AddAssign<$t> for $name {
            fn add_assign(&mut self, x: $t) {
                self.v += x; // Assumed not overflow here
                let p = unsafe { $p };
                if self.v >= p {
                    self.v -= p;
                }
            }
        }
        impl std::ops::Add<$t> for $name {
            type Output = Self;
            fn add(mut self, x: $t) -> Self {
                self += x;
                self
            }
        }
        impl std::ops::AddAssign for $name {
            fn add_assign(&mut self, x: Self) {
                *self += x.v;
            }
        }
        impl std::ops::Add for $name {
            type Output = Self;
            fn add(self, x: Self) -> Self {
                self + x.v
            }
        }
    };
    ($name:ident, $t:ty, $mul_t: ty, $p:ident) => {
        define_mod_val_static!($name, $t, $p);
        impl std::ops::Mul<$t> for $name {
            type Output = Self;
            fn mul(self, x: $t) -> Self {
                let p = unsafe { $p };
                Self::from((self.v as $mul_t * x as $mul_t % p as $mul_t) as $t)
            }
        }
        impl std::ops::Mul for $name {
            type Output = Self;
            fn mul(self, x: Self) -> Self {
                self * x.v
            }
        }
    };
}
static mut P_USIZE: usize = 0;
define_mod_val_static!(ModValUsize, usize, P_USIZE);
static mut P_I32: i32 = 0;
define_mod_val_static!(ModValI32, i32, i64, P_I32);