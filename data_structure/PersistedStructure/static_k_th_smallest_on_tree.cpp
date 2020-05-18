struct PST : public PST_base {
	//return the k_th smallest value in (L, R]
	int Query(int L_rt, int R_rt, int lca_rt, int fa_lca_rt, int l, int r, int k) {
		if (l == r)
			return l;
		int mid = (l + r) >> 1;
		int sum_lc = data[lson[R_rt]] - data[lson[fa_lca_rt]] + data[lson[L_rt]] - data[lson[lca_rt]];
		if (sum_lc >= k)
			return Query(lson[L_rt], lson[R_rt], lson[lca_rt], lson[fa_lca_rt], l, mid, k);
		else
			return Query(rson[L_rt], rson[R_rt], rson[lca_rt], rson[fa_lca_rt], mid+1, r, k - sum_lc);
	}
};

