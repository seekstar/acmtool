int h(int x, int xs[], int xl) {
    return lower_bound(xs + 1, xs + xl + 1, x) - xs;
}
void Discretize(int xs[], int& xl) {
    sort(xs + 1, xs + xl + 1);
    xl = unique(xs + 1, xs + xl + 1) - xs - 1;
}

