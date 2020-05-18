//quo = a / b
//Allow quo == a or b
//b is reversed
void Div(vi& quo, vi& a, vi& b) {
    static vi t(MAX2N);
    int nq = a.size() - b.size() + 1;	//length of quo
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    int len = FindPowOf2(nq), nb = b.size();
    Fill(b, len);
    Inv(t, b, len);
    b.resize(nb);
    a.resize(len, 0);
    Mul(quo, a, t);
    quo.resize(nq);
    reverse(quo.begin(), quo.end());
}
//quo != a && quo != b
//rem != a
//Allow rem == b
//len(rem) == nb - 1
void DivMod(vi& quo, vi& rem, const vi& a, vi& b) {
    static vi t(MAX2N);
    t = a;
    Div(quo, t, b);
    reverse(b.begin(), b.end());	//reverse back
    t = quo;
    int nb = b.size();
    Mul(rem, t, b);
    rem.resize(nb - 1);
    for (int i = 0; i < rem.size(); ++i)
        rem[i] = Sub(a[i] - rem[i], p);
}
