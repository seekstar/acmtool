//n is the length of the array that required
//if table[i] < i,then i means a,and table[i] means b.Else,i means b,ans table[i] means a.
int* MakeWythoffTable(int n)
{
    int k;
    int* table = new int[n];
    int a;

    for(k = 0; k < n; k++)
    {
        a = k * mul;
        if(a >= n)
            break;
        table[a] = a + k;
        if(a + k < n)
            table[a+k] = a;
    }

    return table;
}
