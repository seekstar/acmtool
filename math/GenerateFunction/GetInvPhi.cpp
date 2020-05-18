//Get 1 / \prod_{i=1}^{\infty} (1 - x^i)
int Five(int x) {
    return (3 * x * x - x) / 2;
}
void GetInvPhi(int ps[], int N, int p) {
    ps[0] = ps[1] = 1;
    for (int n = 2; n <= N; ++n) {
        ps[n] = 0;
        for (int i = 1; ; i = i < 0 ? 1 - i : -i) {
            int now = n - Five(i);
            if (now < 0)
                break;
            if (i & 1) {
                AddMod(ps[n] += ps[now], p);
            } else {
                SubMod(ps[n] -= ps[now], p);
            }
        }
    }
}

