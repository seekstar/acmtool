typedef double FUNC(double);
double GetRoot_bsearch(FUNC f, double l, double r, bool leftMinus, double eps) {
	while (r - l > eps) {
		double mid = (l + r) / 2;
		bool midMinus = (f(mid) < 0);
		if (leftMinus ^ midMinus) {
			r = mid;
		} else {
			l = mid;
			leftMinus = midMinus;
		}
	}
	return (l+r)/2;
}


