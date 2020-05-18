//O(nlog n)
template <typename T>
int LIS(const T a[], int n) {
    static T s[MAXN];   //smallest
    if (0 == n) return 0;
    s[0] = a[0];
    int len = 1;
    for (int i = 1; i < n; ++i) {
        int pos = lower_bound(s, s + len, a[i]) - s;	//If upper_bound, then the result is the longest not decreasing sub sequence
        if (pos == len) ++len;
        s[pos] = a[i];
    }
    return len;
}
