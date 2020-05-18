void GetSegs(SEG sgs[], const VEC ps[], int n) {
    if (dir(ps, n)) {
        sgs[n-1] = SEG(ps[n-1], ps[0]);
        for (int i = 0; i < n-1; ++i)
            sgs[i] = SEG(ps[i], ps[i+1]);
    } else {
        sgs[0] = SEG(ps[0], ps[n-1]);
        for (int i = 1; i < n; ++i)
            sgs[i] = SEG(ps[i], ps[i-1]);
    }
}

