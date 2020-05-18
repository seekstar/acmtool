struct DISJOINT {
    //static const int maxn = MAXN;
    int s[maxn];

    void Init(int n){
        memset(s, -1, (n+1) * sizeof(s[0]));
    }
    int FindRoot(int a){
        return s[a] < 0 ? a : (s[a] = FindRoot(s[a]));
    }
    void Union(int a, int b){
        UnionRoot(FindRoot(a), FindRoot(b));
    }
    void UnionRoot(int a, int b){
        if(a == b)return;
        if(s[a] > s[b])
            swap(a,b);
        s[a] += s[b];
        s[b] = a;
    }
};


//simple
struct DISJOINT{
    int s[MAXN_DISJOINT];

    void Init(int n){
        memset(s, -1, (n+1) * sizeof(s[0]));
    }
    int FindRoot(int a){
        int b = a;
        while(s[a] >= 0)
            a = s[a];
        while(s[b] >= 0){
            int tmp = s[b];
            s[b] = a;
            b = tmp;
        }
        return a;
    }
    void UnionRoot(int a, int b){
        if(a != b)
            s[b] = a;
    }
    void Union(int a, int b){
        UnionRoot(FindRoot(a), FindRoot(b));
    }
};


//DISJOINT with value
template<typename DistType>
struct DISJOINT_VAL{
    int s[MAX_NODE_DISJOINT_VAL];
    DistType d[MAX_NODE_DISJOINT_VAL];

    void Init(int n){
        memset(s, -1, (n+1) * sizeof(s[0]));
        memset(d, 0, (n+1) * sizeof(d[0]));
    }
    DistType RootDist(int& a){
        int b = a;
        DistType sum_d = 0;
        DistType pre_d = 0;
        while(s[a] >= 0){
            sum_d += d[a];
            a = s[a];
        }
        while(b != a){
            int tmp = s[b];
            s[b] = a;
            DistType tmp_d = d[b];
            d[b] = sum_d - pre_d;
            pre_d += tmp_d;
            b = tmp;
        }
        return sum_d;
    }
    //d_ba means the distance from b to a
    //Assume that a != b
    void UnionRoot(int a, int b, DistType d_ba){
        s[b] = a;
        d[b] = d_ba;
    }
    void Union(int a, int b, DistType d_ba){
        DistType d_a = RootDist(a);
        DistType d_b = RootDist(b);
        UnionRoot(a, b, d_a + d_ba - d_b);
    }
};
