//t = 100, rate = 0.98
BALL SmallestBallCover(const VEC ps[], int n, double t, double rate) {
    BALL ball{{0, 0, 0}, numeric_limits<double>::max()};
    while (t > eps) {
        double mx = 0;
        int s = 0;
        for (int i = 0; i < n; ++i) {
            double now = ball.c.dist(ps[i]);
            if (now > mx) {
                mx = now;
                s = i;
            }
        }
        ball.r = min(ball.r, mx);
        ball.c = ball.c + (ps[s] - ball.c) / mx * t;    //In case that the step is too big when ball.r is too big
        t *= rate;
    }
    return ball;
}

default_random_engine e(time(NULL));
BALL SmallestBallCover(VEC ps[], int n) {
    shuffle(ps, ps + n, e);
    BALL ball{ps[0], 0};
    for (int i1 = 1; i1 < n; ++i1) {
        if (ball.relation(ps[i1]) == 1) {
            ball.c = ps[i1];
            for (int i2 = 0; i2 < i1; ++i2) {
                if (ball.relation(ps[i2]) == 1) {
                    ball.SetCircumscribed(ps[i1], ps[i2]);
                    for (int i3 = 0; i3 < i2; ++i3) {
                        if (ball.relation(ps[i3]) == 1) {
                            ball.SetCircumscribed(ps[i1], ps[i2], ps[i3]);
                            for (int i4 = 0; i4 < i3; ++i4) {
                                if (ball.relation(ps[i4]) == 1) {
                                    ball.SetCircumscribed(ps[i1], ps[i2], ps[i3], ps[i4]);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return ball;
}
