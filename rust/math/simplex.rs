// max c x
// ax = b
// x >= 0
// xb: Indexes of base variables in each row
fn simplex_base(
    a: &mut Vec<Vec<f64>>,
    b: &mut Vec<f64>,
    c: &Vec<f64>,
    xb: &mut Vec<usize>,
    eps: f64,
) -> f64 {
    let n = c.len();
    let m = b.len();
    let mut xbs = HashSet::with_capacity(m);
    for i in xb.iter() {
        xbs.insert(*i);
    }
    let mut cb = Vec::with_capacity(n);
    for i in 0..m {
        cb.push(c[xb[i]]);
    }
    let mut z = 0.0;
    for i in 0..m {
        z += c[xb[i]] * b[i];
    }
    loop {
        let mut j = 0;
        let mut l = 0;
        let mut lambda = 0.0;
        while j < n {
            if xbs.get(&j).is_some() {
                j += 1;
                continue;
            }
            let mut s = 0.0;
            for i in 0..m {
                s += cb[i] * a[i][j];
            }
            s = c[j] - s;
            if s > eps {
                lambda = s;
                let mut beta = f64::INFINITY;
                for i in 0..m {
                    if a[i][j] < eps {
                        continue;
                    }
                    let tmp = b[i] / a[i][j];
                    if tmp < beta {
                        beta = tmp;
                        l = i;
                    }
                }
                if beta.is_finite() {
                    z += beta * lambda;
                    break;
                }
                // Otherwise all a[*][j] <= 0
                // TODO: Must be unbounded?
            }
            j += 1;
        }
        if j == n {
            if lambda > eps {
                // Unbounded
                return f64::INFINITY;
            } else {
                return z;
            }
        }
        b[l] /= a[l][j];
        let tmp = a[l][j];
        for k in 0..n {
            a[l][k] /= tmp;
        }
        for i in 0..m {
            if i == l {
                continue;
            }
            let tmp = a[i][j];
            if tmp < -eps || tmp > eps {
                b[i] -= b[l] * tmp;
                for k in 0..n {
                    a[i][k] -= a[l][k] * tmp;
                }
            }
        }
        xbs.remove(&xb[l]);
        xbs.insert(j);
        xb[l] = j;
        cb[l] = c[j];
    }
}

// max c x
// ax = b
// x >= 0
fn simplex(
    a: &mut Vec<Vec<f64>>,
    b: &mut Vec<f64>,
    c: &Vec<f64>,
    eps: f64,
) -> (f64, Vec<usize>) {
    let n = c.len();
    let m = b.len();
    // Artificial variables
    let mut ca = vec![0.0; n];
    ca.resize(n + m, -1.0);
    for i in 0..m {
        a[i].resize(n + m, 0.0);
    }
    for i in 0..m {
        a[i][n + i] = 1.0;
    }
    let mut xb = Vec::with_capacity(m);
    for i in n..(n+m) {
        xb.push(i);
    }
    simplex_base(a, b, &ca, &mut xb, eps);
    for i in xb.iter() {
        let i = *i;
        if i >= n {
            // Artificial variables still exist in base
            // No solution
            return (f64::NAN, xb);
        }
    }
    for i in 0..m {
        a[i].truncate(n);
    }
    (simplex_base(a, b, c, &mut xb, eps), xb)
}


// max c x
// ax = b
// x >= 0
fn simplex_big_m(
    a: &mut Vec<Vec<f64>>,
    b: &mut Vec<f64>,
    c: &mut Vec<f64>, // Actually not changed
    eps: f64,
    big_m: f64,
) -> (f64, Vec<usize>) {
    let n = c.len();
    let m = b.len();
    // Artificial variables
    // c.resize(c.len() + m, f64::NEG_INFINITY);
    c.resize(c.len() + m, -big_m);
    for i in 0..m {
        a[i].resize(n + m, 0.0);
    }
    for i in 0..m {
        a[i][n + i] = 1.0;
    }
    let mut xb = Vec::with_capacity(m);
    for i in n..(n+m) {
        xb.push(i);
    }
    let ret = simplex_base(a, b, c, &mut xb, eps);
    for i in xb.iter() {
        let i = *i;
        if i >= n {
            // Artificial variables still exist in base
            // No solution
            return (f64::NAN, xb);
        }
    }
    c.truncate(c.len() - m);
    for i in 0..m {
        a[i].truncate(n);
    }
    (ret, xb)
}