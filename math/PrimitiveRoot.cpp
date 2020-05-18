template <typename T>
T PrimitiveRoot(T m) {
    vector<T> factor;
    PrimeFactor(m, factor);
    T phi = m;
    for (T v : factor)
        (phi /= v) *= (v - 1);
    PrimeFactor(phi, factor);
    for (T g = 2, i; g < m; ++g) {
        for (i = 0; i < factor.size(); ++i)
            if (mpow(g, phi / factor[i], m) == 1)
                break;
        if (i == factor.size())
            return g;
    }
    return -1;
}
