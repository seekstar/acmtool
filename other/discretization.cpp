int h(int x, int xs[], int xl) {
    return lower_bound(xs, xs + xl, x) - xs;
}
void Discretize(int xs[], int& xl) {
    sort(xs, xs + xl);
    xl = unique(xs, xs + xl) - xs;
}

