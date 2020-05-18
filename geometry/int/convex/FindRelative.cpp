//Three point search
//If w == 1, find the rightmost point relative to p. if w == -1, find the leftmost.
int FindRelative(const VEC ps[], int L, int R, const VEC& p, int w) {
    while (L < R) {
        int mid = (L + R) >> 1;
        if (((ps[mid] - p) ^ (ps[mid+1] - p)) * w > 0)
            R = mid;
        else
            L = mid + 1;
    }
    return L;
}
