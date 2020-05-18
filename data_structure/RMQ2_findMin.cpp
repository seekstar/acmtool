//RMQ in 2 dimension (Range Minimum/Maximum Query)
//if cmp is min, than it returns the minimum number.
template<typename NumType, const NumType& cmp(const NumType&, const NumType&) >
struct RMQ2
{
    NumType f[MAX][MAX][BIT1][BIT2];//��f[i][j][k][p]��ʾ(i,j)��(i+2^k,j+2^p)�����ڵ���Сֵ
    int N, M;

    void Init(NumType data[MAX][MAX], int n, int m)
    {
        int i, j, k, p;
        N = n;
        M = m;
        for(i = 1; i <= N; i++)
            for(j = 1; j <= M; j++)
                f[i][j][0][0] = data[i][j];
        for(k = 1; (1 << k) <= N; k++)
            for(p = 1; (1<<p) <= M; p++)
                for(i = 1; i + (1<<k) - 1 <= N; i++)
                    for(j = 1; j + (1<<p) - 1 <= M; j++)
                    {
                        f[i][j][k][p] = f[i][j][k-1][p-1];
                        f[i][j][k][p] = cmp(f[i][j][k][p], f[i+(1<<(k-1))][j][k-1][p-1]);
                        f[i][j][k][p] = cmp(f[i][j][k][p], f[i][j+(1<<(p-1))][k-1][p-1]);
                        f[i][j][k][p] = cmp(f[i][j][k][p], f[i+(1<<(k-1))][j+(1<<(p-1))][k-1][p-1]);
                    }
    }
    NumType Query(int i, int j, int sn, int sm)//sn * sm
    {
        int k,p;
        NumType ans;
        for(k = 0; (1<<(k+1)) <= sn; k++);
        for(p = 0; (1<<(p+1)) <= sm; p++);

        ans = f[i][j][k][p];
        ans = cmp(ans, f[i+sn-(1<<k)][j][k][p]);
        ans = cmp(ans, f[i][j+sm-(1<<p)][k][p]);
        ans = cmp(ans, f[i+sn-(1<<k)][j+sm-(1<<p)][k][p]);
        return ans;
    }
};
