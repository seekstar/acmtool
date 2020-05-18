//RMQ(Range Minimum/Maximum Query)
//if cmp is min, than it returns the minimum number.
template<typename NumType, const NumType& cmp(const NumType&, const NumType&) >
struct RMQ
{
    NumType f[MAX][BIT];//用f[i][k]表示[i,i+2^k)的最小值
    int N;

    void Init(NumType data[MAX], int n)
    {
        int i, k;
        N = n;
        for(i = 1; i <= N; i++)
            f[i][0] = data[i];
        for(k = 1; (1 << k) <= N; k++)
            for(i = 1; i + (1<<k) - 1 <= N; i++)
                f[i][k] = cmp(f[i][k-1], f[i+(1<<(k-1))][k-1]);
    }
    NumType Query(int i, int sn)    //The minimal of [i, i+sn)
    {
        int k;
        for(k = 0; (1<<(k+1)) <= sn; ++k);

        return cmp(f[i][k], f[i+sn-(1<<k)][k]);
    }
};
