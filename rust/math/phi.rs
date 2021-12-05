// O(sqrt(n))
// phi(1) = 1
fn phi(mut n: u32) -> u32 {
    let mut ans = n;
    let mut i = 2u32;
    while i as u64 * i as u64 <= n as u64 {
        if n % i == 0 {
            ans = ans / i * (i - 1);
            loop {
                n /= i;
                if n % i != 0 {
                    break;
                }
            }
        }
        i += 1;
    }
    if n > 1 {
        ans = ans / n * (n - 1);
    }
    ans
}
