//Interval cross
pii Cross(pii x, pii y) {
    return make_pair(max(x.first, y.first), min(x.second, y.second));
}

