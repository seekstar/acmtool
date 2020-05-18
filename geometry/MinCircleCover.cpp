default_random_engine e(time(NULL));
//O(n)
CIRCLE MinCircleCover(VEC ps[], int n) {
    shuffle(ps, ps + n, e);
    CIRCLE o{ps[0], 0};
    for (int i = 1; i < n; ++i) {
        if (o.relation(ps[i]) == 1) {
            o.c = ps[i];
            for (int j = 0; j < i; ++j) {
                if (o.relation(ps[j]) == 1) {
                    o = {(ps[i] + ps[j]) / 2.0, ps[i].dist(ps[j]) / 2};
                    for (int k = 0; k < j; ++k) {
                        if (o.relation(ps[k]) == 1) {
                            o.SetCircumcircle(ps[i], ps[j], ps[k]);
                        }
                    }
                }
            }
        }
    }
    return o;
}
