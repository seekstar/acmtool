use std::mem;
const MAX_BUCKET: usize = 0x100;
fn radix_sort(base: &mut [usize]) {
    const MAX_BIT: usize = 8 * mem::size_of::<usize>();
    const MASK: usize = MAX_BUCKET - 1;
    let mut a = base;
    let n = a.len();
    let mut buffer = vec![0usize; n];
    let mut b = &mut buffer[..];
    let mut t = vec![0usize; n];
    let mut sa = vec![0usize; n];

    for k in (0..MAX_BIT).step_by(8) {
        let mut c = vec![0usize; MAX_BUCKET];
        for i in 0..n {
            t[i] = (a[i] >> k) & MASK;
            c[t[i]] += 1;
        }
        for i in 1..MAX_BUCKET {
            c[i] += c[i - 1];
        }
        for i in (0..n).rev() {
            c[t[i]] -= 1;
            sa[c[t[i]]] = i;
        }
        for i in 0..n {
            b[i] = a[sa[i]];
        }
        let tmp = a;
        a = b;
        b = tmp;
    }
    if MAX_BIT & 1 != 0 {
        for i in 0..n {
            b[i] = a[i];
        }
    }
}
