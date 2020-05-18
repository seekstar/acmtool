template <typename T>
int manacher( const T* str,int* r,int len,int n ){
    int mx(0),c(1),i,j;
    r[0] = r[len-1] = 1;
    int res = 0;
    for(  i = 1;i < len-1;i++ ){
        if( mx >= i ) j = min( r[ (c<<1)-i ],mx-i+1 );
        else j = 1;
        while((i-j) >= 0 &&  str[i-j] == str[i+j] )++j;
        if( i+j-1 > mx ){
            mx = i+j-1;
            c = i;
        }
        r[i] = j;
        if( (r[i]*2-1)/2 >= n &&(i&1) ) res++;
    }
    return res;
}
template <typename T>
int NumOfPalindromeSplit(const T s[], int n) {
    const static T minf = numeric_limits<T>::min();
    static int r[MAXN*8+7];
    static T str[MAXN*8+7];
    for( int i = 0;i < n;i++ ){
        str[i<<1] = minf;
        str[i<<1|1] = s[i];
    }
    for( int i = 0;i < n*2;i++ ){
        str[i+(n<<1)] = str[i];
    }
    str[n*4] = minf;
    int len = n*2+1;
    return manacher( str,r,len,n );
}
int NumOfAxisOfSymmetry(const VEC ps[], int n) {
    assert(n >= 3);
    static LT ha[MAXN << 1];
    ha[0] = (ps[0] - ps[n-1]).len2();
    ha[1] = ((ps[0] - ps[n-1]) ^ (ps[1] - ps[0]));
    for (int i = 1; i < n; ++i) {
        ha[i << 1] = (ps[i] - ps[i-1]).len2();
        ha[i << 1 | 1] = (ps[i] - ps[i-1]) ^ (ps[Add(i+1, n)] - ps[i]);
    }
    return NumOfPalindromeSplit(ha, n << 1);
}