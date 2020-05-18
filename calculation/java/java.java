Vector sons = new Vector(size);
Vector is generalized list


ArrayList才相当于C++的vector
ArrayList<BigInteger> a = new ArrayList<BigInteger>();
a.add(BigInteger.valueOf(3));
a.get(i-1).multiply(BigInteger.valueOf(7))

ArrayList转数组：
BigInteger[] head = a.toArray(new BigInteger[a.size()]);


可以这样：
int sons[][] = new int[n+1]
for (int i = 1; i <= n; ++i) {
	int m = in.nextInt();
	sons[i] = new int[m+1];
}



Math.max()


EOF结束输入：
while (in.hasNext())


泛型方法：
public static <T extends Comparable<T> > boolean cmp(T x, T y) {
	return x.compareTo(y) <= 0;
}
cmp(BigInteger.valueOf(3), BigInteger.valueOf(4))
cmp(3, 4)


BigInteger转BigDecimal:
BigInteger b = BigInteger.ONE;
BigDecimal a = new BigDecimal(b);

BigDecimal转BigInteger:
BigInteger b = a.toBigInteger();


BigDecimal除法限制精度：
now = now.divide(ori, 100, RoundingMode.HALF_UP);

String转BigInteger
new BigInteger("3924140458981690736793364"),


