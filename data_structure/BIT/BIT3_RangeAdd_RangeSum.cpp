//interval add, interval sum
template<typename NumType>
struct BIT3
{
	BIT<NumType> d;
	BIT<NumType> id;	//i * d[i]

	void Init(int n)
	{
		d.Init(n);
		id.Init(n);
	}
	void Add(int l, int r, NumType v)
	{
		d.Add(l, v);
		d.Add(r+1, -v);
		id.Add(l, l * v);
		id.Add(r+1, -(r+1) * v);
	}
	NumType sum(int x)
	{
		return (x+1) * d.sum(x) - id.sum(x);
	}
};
