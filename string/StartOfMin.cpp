int StartOfMin(const char s[], int n) {
    int i = 0, j = 1, k = 0;
    while (i < n && j < n && k < n) {
        int t = s[Add(i + k, n)] - s[Add(j + k, n)];
        if (0 == t) {
            ++k;
        } else {
            if (t > 0) {
                i += k + 1;
            } else {
                j += k + 1;
            }
            if (i == j) ++j;
            k = 0;
        }
    }
    return min(i, j);
}