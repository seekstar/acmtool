struct PST : public PST_BASE {
	int Query(int L_rt, int R_rt, int l, int r, int k) {
		if (l == r)
			return l;
		int mid = (l+r) >> 1;
		int data_lc = data[lson[R_rt]] - data[lson[L_rt]];
		if (data_lc >= k)
			return Query(lson[L_rt], lson[R_rt], l, mid, k);
		else
			return Query(rson[L_rt], rson[R_rt], mid+1, r, k-data_lc);
	}
};

