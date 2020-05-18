//Anticlockwise is plus
LT area2_di(const VEC ps[], int n) {
    LT ans = ps[n-1] ^ ps[0];
    for (int i = 0; i < n-1; ++i)
        ans += ps[i] ^ ps[i + 1];
    return ans;
}
