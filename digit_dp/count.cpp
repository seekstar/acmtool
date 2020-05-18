//The number of pairs <x, y> such that 0 <= x && x <= A && 0 <= y && y <= B && (x&y) <= c && (x^y) >= C
LL A, B, C;
LL dp[111][2][2][2][2];
LL f(int in, int oa, int ob, int oand, int oxor) {
    if (in == -1)
        return 1;
    LL& ans = dp[in][oa][ob][oand][oxor];
    if (ans != -1)
        return ans;
    ans = 0;
    bool Ai = A & (1LL << in);
    bool Bi = B & (1LL << in);
    bool Ci = C & (1LL << in);
    int up1 = oa ? Ai : 1;
    int up2 = ob ? Bi : 1;
    for (int i = 0; i <= up1; ++i) {
        int ooa = oa && (i == up1);
        for (int j = 0; j <= up2; ++j) {
            if (oand && (i & j) > Ci) continue;
            if (oxor && (i ^ j) < Ci) continue;
            ans += f(in-1, ooa, ob && (j == up2), oand && ((i & j) == Ci), oxor && ((i ^ j)== Ci));
        }
    }
    return ans;
}

