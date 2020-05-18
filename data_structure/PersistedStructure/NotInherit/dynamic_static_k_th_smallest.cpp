//Get the k_th smallest value
//If you RE, try to modify MAX_SEG_NODE
//#define MAX_SEG_NODE (MAXN * LOG_MAXN + MAXM * LOG_MAXN * LOG_MAXN)
struct PersistedSegTree{
    int a[MAXN];
    int n;      //The length of the array
    int maxv;   //The max val
    int roots[MAXN], lson[MAX_SEG_NODE], rson[MAX_SEG_NODE], data[MAX_SEG_NODE], roots_dy[MAXN];
    int tot;

    //Assume that a, n and maxv were given
    void Init()
    {
        tot = 0;
        roots[0] = Build(1, maxv);
        for(int i = 1; i <= n; ++i) {
            roots[i] = Update(roots[i-1], a[i], 1);
            roots_dy[i] = roots[0];
        }
    }
    //Build an empty tree
    //The lc and rc of a leaf node is meaningless
    int Build(int l, int r)
    {
        int rt = ++tot;
        data[rt] = 0;
        if(l < r) {
            int mid = (l+r) >> 1;
            lson[rt] = Build(l, mid);
            rson[rt] = Build(mid+1, r);
        }
        return rt;
    }
    //A new value x is inserted
    //from: The index of the root of the tree which this update is based on.
    //return the index of the root of the new tree.
    int Update(int from, int x, int num)
    {
        int rt = ++tot;
        int tmp = rt;

        data[rt] = data[from] + num;
        int l = 1, r = maxv;
        while (l < r) {
            int mid = (l + r) >> 1;
            if (x <= mid) {
                rson[rt] = rson[from];
                from = lson[from];
                r = mid;
                rt = lson[rt] = ++tot;
            } else {
                lson[rt] = lson[from];
                from = rson[from];
                l = mid + 1;
                rt = rson[rt] = ++tot;
            }
            data[rt] = data[from] + num;
        }
        return tmp;
    }

    inline int lowbit(int n){
        return n & -n;
    }
    void AddLikeBIT(int i, int x, int num){
        for(; i <= n; i += lowbit(i))
            roots_dy[i] = Update(roots_dy[i], x, num);
    }
    void ChangeLikeBIT(int base[], int i, int x){
        AddLikeBIT(i, base[i], -1);
        AddLikeBIT(i, x, 1);
        base[i] = x;
    }

    void UpdateDyRoot(int L_dy[], int R_dy[], int next[])
    {
        for (int i = 1; i <= L_dy[0]; ++i)
            L_dy[i] = next[L_dy[i]];
        for (int i = 1; i <= R_dy[0]; ++i)
            R_dy[i] = next[R_dy[i]];
    }
    int GetLeftSumLikeBIT(int dy_rt[]){
        int ans = 0;
        for (int i = 1; i <= dy_rt[0]; ++i)
            ans += data[lson[dy_rt[i]]];
        return ans;
    }
    //k_th smallest value in (left, right]
    int QueryLikeBIT(int left, int right, int k){
        static int L_dy[MAXN], R_dy[MAXN];
        int left_rt = roots[left];
        int right_rt = roots[right];

        L_dy[0] = R_dy[0] = 0;
        for(int i = left; i; i ^= lowbit(i))
            L_dy[++L_dy[0]] = roots_dy[i];
        for(int i = right; i; i ^= lowbit(i))
            R_dy[++R_dy[0]] = roots_dy[i];
        int l = 1, r = maxv;
        while(l < r){
            int mid = (l + r) >> 1;
            int sum_lc = GetLeftSumLikeBIT(R_dy) - GetLeftSumLikeBIT(L_dy) + data[lson[right_rt]] - data[lson[left_rt]];
            if(sum_lc >= k){
                r = mid;
                UpdateDyRoot(L_dy, R_dy, lson);
                left_rt = lson[left_rt];
                right_rt = lson[right_rt];
            }
            else{
                l = mid+1;
                k -= sum_lc;
                UpdateDyRoot(L_dy, R_dy, rson);
                left_rt = rson[left_rt];
                right_rt = rson[right_rt];
            }
        }
        return l;
    }
};
