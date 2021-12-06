fn get_invs(invs: &mut [u32], p: u32, n: u32) {
    invs[1] = 1;
    for i in 2..(n + 1) {
        invs[i as usize] = (((p - p / i) as u64) * (invs[(p % i) as usize] as u64) % p as u64) as u32;
    }
}
