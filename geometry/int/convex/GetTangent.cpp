//If p is in the convex, L = -1 && R = -1
//sp is the index of the top right point. (split)
void GetTangent(VEC ps[], int sp, int n, const VEC& p, int& L, int& R) {
    ps[n] = ps[0];
    L = R = -1;
    if (SEG(ps[0], ps[1]).OnSeg(p) || SEG(ps[sp], ps[sp+1]).OnSeg(p)) return;
    if (p.y <= ps[0].y) {
        L = FindRelative(ps, sp, n, p, -1);
        R = FindRelative(ps, 0, sp, p, 1);
    } else if (p.y >= ps[sp].y) {
        L = FindRelative(ps, 0, sp, p, -1);
        R = FindRelative(ps, sp, n, p, 1);
    } else if ((ps[sp] - ps[0]).ToRightTest(p - ps[0])) {    //right
        int mid = lower_bound_y(ps, 0, sp, p.y, 1);
        if (!(ps[mid] - ps[mid-1]).ToRightTest(p - ps[mid-1])) return;
        L = FindRelative(ps, 0, mid-1, p, -1);
        R = FindRelative(ps, mid, sp, p, 1);
    } else {    //right
        int mid = lower_bound_y(ps, sp, n, p.y, -1);
        if (!(ps[mid] - ps[mid-1]).ToRightTest(p - ps[mid-1])) return;
        L = FindRelative(ps, sp, mid-1, p, -1);
        R = FindRelative(ps, mid, n, p, 1);
    }
    R %= n;
}