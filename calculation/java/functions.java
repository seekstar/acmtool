public static int lower_bound(BigInteger[] s, int n, BigInteger x) {
	int L = 0, R = n - 1;
	while (L <= R) {
		int mid = (L + R) >> 1;
		if (s[mid].compareTo(x) < 0) {
			L = mid + 1;
		} else {
			R = mid - 1;
		}
	}
	return R + 1;
}

