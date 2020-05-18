//Interval Add, point value
template<typename NumType>
struct BIT2 {
    BIT<NumType> d;	//diff array

    void Init(int n) {
        d.Init(n+1);
    }
    void Add(int L, int R, NumType v) {
        d.Add(L, v);
        d.Add(R+1, -v);
    }
    NumType at(int x) {
        return d.Sum(x);
    }
};
