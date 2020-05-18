int LongestPalindrome(const string& str)
{
    string mstr;
    int i;
    int maxR;

    mstr.reserve(str.size() * 2 + 2);
    mstr.push_back('!');

    for(i = 0; i < (int)str.size(); i++)
    {
        mstr.push_back(str[i]);
        mstr.push_back('#');
    }
    mstr[mstr.size()-1] = '@';
    int r[mstr.size()];
    Manacher(mstr, r, mstr.size());

    maxR = 0;
    for(i = 1; i < (int)mstr.size()-1; i++)
    {
        if(mstr[i - r[i] + 1] == '#')
        {
            if(maxR < r[i]-1)
            {
                maxR = r[i]-1;
            }
        }
        else
        {
            if(maxR < r[i])
            {
                maxR = r[i];
            }
        }
    }
    return maxR;
}

//前后要填充不同的奇怪的字符
void Manacher(const string& str, int *r, int len)
{
    int mx = 0, c = 1, k;

    for(k = 1; k < len - 1; k++)
    {
        if(mx >= k)
        {
            r[k] = min(r[2*c-k], mx - k + 1);
        }
        else
        {
            r[k] = 1;
        }
        for(; str[k - r[k]] == str[k + r[k]]; r[k]++);

        if(k + r[k] - 1 > mx)
        {
            mx = k + r[k] - 1;
            c = k;
        }
    }
}
