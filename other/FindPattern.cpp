bool Check(int a[], int n, const vector<int>& arr) {
    int i;
    for (i = n; i < arr.size(); ++i) {
        int now = 0;
        for (int j = 0; j < n; ++j) {
            now += arr[i - j - 1] * a[j];
        }
        if (now != arr[i]) break;
    }
    return i >= arr.size();
}

int f(int x) {
    int y = x >> 1;
    return x & 1 ? -y - 1 : y;
}

void find(int a[], const vector<int>& arr) {
    const int to = 100;
    for (int i = 0; i < to; ++i) {
        a[3] = f(i);
        for (int i = 0; i < to; ++i) {
            a[2] = f(i);
            for (int i = 0; i < to; ++i) {
                a[1] = f(i);
                for (int i = 0; i < to; ++i) {
                    a[0] = f(i);
                    if (Check(a, 4, arr)) return;
                }
            }
        }
    }
}
