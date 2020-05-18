//__uint128
typedef unsigned long long ULL;
typedef unsigned int UINT;
bool AddEqULL(ULL& lhs, ULL rhs){
    static const ULL HighBit = 1ULL << 63U;
    bool both = (lhs & HighBit) && (rhs & HighBit);
    bool one = (lhs & HighBit) || (rhs & HighBit);
    lhs += rhs;
    return both || (one && !(lhs & HighBit));
}
bool SubEqULL(ULL& lhs, ULL rhs) {
	bool ans = lhs < rhs;
	lhs -= rhs;
	return ans;
}
struct _uint128{
    static const ULL ML32 = 0xffffffffULL;	//mask low32
    static const ULL MH32 = 0xffffffff00000000ULL;
    ULL H;  //Higher 64 bit
    ULL L;  //Lower 64 bit
    _uint128() = default;
    _uint128(UINT x){
        *this = x;
    }
    _uint128(ULL _H, ULL _L){
        H = _H;
        L = _L;
    }

    explicit operator bool(){
        return L || H;
    }
	explicit operator ULL() {
		return L;
	}
    bool operator < (const _uint128 &rhs) const{
        return H != rhs.H ? H < rhs.H : L < rhs.L;
    }

    _uint128& operator += (const _uint128 &rhs){
        if(AddEqULL(L, rhs.L))
            ++H;
        H += rhs.H;
        return *this;
    }
    _uint128 operator + (const _uint128& rhs) const{
        _uint128 ans = *this;
        ans += rhs;
        return ans;
    }

	_uint128& operator -= (const _uint128& rhs) {
		if (SubEqULL(L, rhs.L))
			--H;
		H -= rhs.H;
		return *this;
	}
	_uint128 operator - (const _uint128& rhs) const {
		auto tmp = *this;
		return tmp -= rhs;
	}

    _uint128& operator = (UINT rhs){
        L = rhs;
        H = 0;
        return *this;
    }

    _uint128& operator *= (UINT rhs){
        ULL tmp = (L & ML32) * rhs;
        L = (L & MH32) | (tmp & ML32);
        tmp >>= 32U;
        bool of = AddEqULL(tmp, (L >> 32U) * rhs);
        L = (L & ML32) | ((tmp & ML32) << 32U);
        tmp >>= 32U;
        if(of){
            ++tmp;
        }
        of = AddEqULL(tmp, (H & ML32) * rhs);
        H = (H & MH32) | (tmp & ML32);
        tmp >>= 32U;
        if(of){
            ++tmp;
        }
        AddEqULL(tmp, (H >> 32U) * rhs);
        H = (H & ML32) | ((tmp & ML32) << 32U);
        return *this;
    }
    _uint128 operator * (UINT rhs) const{
        _uint128 ans = *this;
        ans *= rhs;
        return ans;
    }
    _uint128 operator - () const{
        _uint128 ans(~H, ~L);
        ans += (_uint128)1;
        return ans;
    }
    _uint128& DivEqMod(ULL& rem, UINT x){
        rem = H % x;
        H /= x;
        rem <<= 32U;
        rem += L >> 32U;
        L = (L & ML32) | ((rem / x) << 32U);
        rem %= x;
        rem <<= 32U;
        rem += L & ML32;
        L = (L & MH32) | (rem / x);
        rem %= x;
        return *this;
    }
	_uint128& operator /= (UINT x) {
		ULL rem;
		DivEqMod(rem, x);
		return *this;
	}
	_uint128 operator / (UINT x) const {
		auto tmp = *this;
		return tmp /= x;
	}
    _uint128& operator <<= (UINT x){
        H <<= x;
        H |= (L >> (64U-x));
        L <<= x;
        return *this;
    }
    _uint128 operator << (UINT x){
        _uint128 ans = *this;
        ans <<= x;
        return ans;
    }
};
void output(_uint128 x){
    static char buf[100];
    static int t;
    do{
        ULL rem;
        x.DivEqMod(rem, 10);
        buf[t++] = rem + '0';
    }while(x);
    while(t)putchar(buf[--t]);
}
