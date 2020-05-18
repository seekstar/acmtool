//if ps.y is increasing, w == 1, else w == -1
int lower_bound_y(const VEC ps[], int L, int R, LT y, int w) {
    while (L < R) {
        int mid = (L + R) >> 1;
        if ((ps[mid].y - y) * w < 0)
            L = mid + 1;
        else
            R = mid;
    }
    return L;
}
