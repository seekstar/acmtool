pub trait Compare<L: ?Sized, R: ?Sized = L> {
    /// Compares two values, returning `Less`, `Equal`, or `Greater` if `l` is less
    /// than, equal to, or greater than `r`, respectively.
    fn compare(&self, l: &L, r: &R) -> Ordering;

    /// Checks if `l` is less than `r`.
    fn compares_lt(&self, l: &L, r: &R) -> bool { self.compare(l, r) == Ordering::Less }

    /// Checks if `l` is less than or equal to `r`.
    fn compares_le(&self, l: &L, r: &R) -> bool { self.compare(l, r) != Ordering::Greater }

    /// Checks if `l` is greater than or equal to `r`.
    fn compares_ge(&self, l: &L, r: &R) -> bool { self.compare(l, r) != Ordering::Less }

    /// Checks if `l` is greater than `r`.
    fn compares_gt(&self, l: &L, r: &R) -> bool { self.compare(l, r) == Ordering::Greater }

    /// Checks if `l` is equal to `r`.
    fn compares_eq(&self, l: &L, r: &R) -> bool { self.compare(l, r) == Ordering::Equal }

    /// Checks if `l` is not equal to `r`.
    fn compares_ne(&self, l: &L, r: &R) -> bool { self.compare(l, r) != Ordering::Equal }
}
