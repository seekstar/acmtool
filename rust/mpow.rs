// Faster?
fn mpow(mut base: u32, mut ex: u32, p: u32) -> u32 {
    let mut ans = 1u32;
    while ex != 0 {
        if ex & 1u32 != 0 {
            ans = (ans as u64 * base as u64 % p as u64) as u32;
        }
        base = (base as u64 * base as u64 % p as u64) as u32;
        ex >>= 1;
    }
    return ans;
}

fn mpow(base: u32, mut ex: u32, p: u32) -> u32 {
    let mut ans = 1u64;
    let mut base = base as u64;
    let p = p as u64;
    while ex != 0 {
        if ex & 1u32 != 0 {
            ans = ans * base % p;
        }
        base = base * base % p;
        ex >>= 1;
    }
    return ans as u32;
}

