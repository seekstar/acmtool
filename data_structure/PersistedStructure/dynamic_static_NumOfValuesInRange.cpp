int a[MAXN], n, maxv;
struct PST : public PST_BASE {
	int roots_dy[MAXN_PST];
	void Init() {
		PST_BASE::Init(a, n, maxv+1);
		for (int i = 1; i <= n; ++i)
			roots_dy[i] = roots[0];
	}
	void AddLikeBIT(int i, int x, int num){
        for(; i <= n; i += lowbit(i))
            roots_dy[i] = Insert(roots_dy[i], x, num, maxv+1);
    }

    int GetLeftSumLikeBIT(int dy_rt[]){
        int ans = 0;
        for (int i = 1; i <= dy_rt[0]; ++i)
            ans += data[lson[dy_rt[i]]];
        return ans;
    }
    void UpdateDyRoot(int L_dy[], int R_dy[], int next[])
    {
        for (int i = 1; i <= L_dy[0]; ++i)
            L_dy[i] = next[L_dy[i]];
        for (int i = 1; i <= R_dy[0]; ++i)
            R_dy[i] = next[R_dy[i]];
    }
    //The number of values that in the range [1, x) in (left, right]
    int PrefixSum(int left, int right, int x){
        static int L_dy[MAXN], R_dy[MAXN];
        int left_rt = roots[left];  //static
        int right_rt = roots[right];
        int ans = 0;

        L_dy[0] = R_dy[0] = 0;
        for(int i = left; i; i ^= lowbit(i))
            L_dy[++L_dy[0]] = roots_dy[i];
        for(int i = right; i; i ^= lowbit(i))
            R_dy[++R_dy[0]] = roots_dy[i];
        int l = 1, r = maxv+1;
        while (l < r) {
            int mid = (l + r) >> 1;
            if (x <= mid) {
				r = mid;
				UpdateDyRoot(L_dy, R_dy, lson);
				left_rt = lson[left_rt];
				right_rt = lson[right_rt];
            } else {
            	ans += GetLeftSumLikeBIT(R_dy) - GetLeftSumLikeBIT(L_dy) + data[lson[right_rt]] - data[lson[left_rt]];
				l = mid+1;
				UpdateDyRoot(L_dy, R_dy, rson);
				left_rt = rson[left_rt];
				right_rt = rson[right_rt];
            }
		}
        return ans;
    }
};

