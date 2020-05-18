//O(log(min(a, b)))
//warning:GCD(0, x) == x
//a and b are unordered
template<typename T>
T GCD(T a, T b) {
    T r;
    while(b)
        r = a % b, a = b, b = r;
    return a;
}

/*
warning:GCD(0, x) == x
Return:
	1.若n > 0则返回求得的公共最大公约数
	2.若0 == n则返回0
*/
template<typename T, typename LenType>
T GCDArray(const T *array, LenType n)
{
    LenType i;//循环控制变量
    T answer;//保存最大公约数

    if(0 == n)//输入错误
        return 0;
    answer = abs(array[0]);
    for(i= 1; i < n; i++)
    {
        answer = GCD(abs(array[i]), answer);
        if(1 == answer)break;
    }
    return answer;
}

//Description:求两个数的最小公倍数
template<typename T>
T LCM(T a, T b) {
	return !a || !b ? 0 : a * b / GCD(a, b);
}
/*
Description:求一组数据的公共最小公倍数
Return:
	n > 0:返回求得的公共最大公倍数
	0 == n:返回0
*/
template<typename T, typename LenType>
T LCMArray(const T *array, LenType n)
{
	LenType i;
	T answer;//保存答案

	if(0 == n)
		answer = 0;
	else if(1 == n)
		answer = array[0];
	else
	{
		answer = array[0];
		for(i = 1; i < n; i++)
			answer = LCM(abs(array[i]), abs(answer));
	}
	return answer;
}

//O(log(min(a, b)))
//ax + by = gcd(a,b). x and y may not be the least positive number
template<typename T>
void exgcd(const T& a, const T& b, T& x, T& y) {
    if(b == 0) {
        x = 1;
        y = 0;
        return;
    }
    exgcd(b, a%b, x, y);
    T tmp = x;
    x = y;
    y = tmp - a / b * y;
}
//O(log(num))
//ans * num == 1(mod p)
//num and p should be relatively prime(gcd(num,p) == 1),or there will be no answer
template<typename T>
T Inv(const T& num, const T& p) {
    T ans, tmp;
    exgcd(num, p, ans, tmp);
    return (ans % p + p) % p;
}
//中国剩余定理
//O(n log n)
//Elements in m[] should be relatively prime
//ans == a_i(mod m_i),for any i in [0,len)
template<typename T>
T CRT(const T a[], const T m[], int len) {
    T M = 1, Mi, ans = 0;
    int i;
    for (i = 0; i < len; i++)
        M *= m[i];
    for (i = 0; i < len; i++) {
        Mi = M / m[i];
        ans = (ans + (LL)a[i] * Inv(Mi, m[i]) * Mi) % M;   //Inv use exgcd
    }
    return (ans + M) % M;
}

//拓展中国剩余定理，乘法爆long long
//O(n log n)
//Elements in m[] can be not relatively prime
//ans == a_i(mod m_i) (for all i), ans is the minimum plus solution
//if there is no answer,return -1
template<typename T>
T exCRT(const T a[], const T m[], int len) {
    T x1, x2, nowA = a[0], nowM = m[0];
    for(int i = 1; i < len; i++) {
        T g = exgcd(nowM, m[i], x1, x2);    //x1 = inv(nowM/g)
        if((a[i] - nowA) % g)
            return -1;
        x1 = multi(x1, (a[i] - nowA) / g, m[i] / g);
        T tmp = nowM;
        nowM *= m[i] / g;//LCM(nowM, m[i])
        nowA = (multi(tmp, x1, nowM) + nowA) % nowM;
    }
    return nowA;
}
//Elements in m[] can be not relatively prime
//ans == a_i(mod m_i) (for all i)
//if there is no answer,return -1
SignedBigInt exCRT(const int a[], const int m[], int len) {
    SignedBigInt x1, x2, nowA(a[0]), nowM(m[0]);
    for(int i = 1; i < len; ++i) {
        SignedBigInt g = exgcd(nowM, SignedBigInt(m[i]), x1, x2);    //x1 = inv(nowM/g)
        if((SignedBigInt(a[i]) - nowA) % g)
            return SignedBigInt(-1);
        (x1 *= (SignedBigInt(a[i]) - nowA) / g) %= (SignedBigInt(m[i]) / g);
        auto tmp(nowM);
        nowM *= SignedBigInt(m[i]) / g;//LCM(nowM, m[i])
        (nowA += tmp * x1 % nowM + nowM) %= nowM;
    }
    return nowA;
}

//return gcd(a,b)
//ax + by = gcd(a,b)
template<typename T>
T exgcd(T a, T b, T& x, T& y) {
    if(b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    T ans = exgcd(b, a%b, x, y);
    T tmp = x;
    x = y;
    y = tmp - a / b * y;
    return ans;
}


//unverified
//The answer is plus???
//Do not consider the overflow
//Elements in m[] can be not relatively prime
//ans == a_i(mod m_i) (for all i)
//if there is no answer,return -1
LL exCRT(const int a[], const int m[], int len) {
    LL x1, x2, nowA(a[0]), nowM(m[0]);
    for(int i = 1; i < len; ++i) {
        LL g = exgcd(nowM, LL(m[i]), x1, x2);    //x1 = inv(nowM/g)
        if((LL(a[i]) - nowA) % g)
            return -1;
        (x1 *= (LL(a[i]) - nowA) / g) %= (LL(m[i]) / g);
        auto tmp(nowM);
        nowM *= LL(m[i]) / g;//LCM(nowM, m[i])
        (nowA += tmp * x1 % nowM + nowM) %= nowM;
    }
    return nowA;
}
