//Get the area enclosed by a point and two points of a convex
namespace ENCLOSED {
    LT sum[MAXN];

    //abs(sum[n]) is the area
    void Init(VEC ps[], int n) {
        sum[0] = 0;
        ps[n] = ps[0];
        for (int i = 1; i <= n; ++i)
            sum[i] = sum[i - 1] + (ps[i - 1] ^ ps[i]);
    }
    LT area2(const VEC ps[], int n, int L, int R, const VEC& p) {
        LT now;
        if (L <= R) {
            now = sum[n] - (sum[R] - sum[L]);
        } else {
            now = sum[L] - sum[R];
        }
        now += (ps[L] ^ p) + (p ^ ps[R]);
        return abs(now);
    }
}
