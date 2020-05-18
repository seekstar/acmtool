struct SignedBigInt {
    bool is_minus;
    UnsignedBigInt absVal;

    SignedBigInt() : is_minus(false) {}
    explicit SignedBigInt(int num) : absVal(std::abs(num)), is_minus(num < 0) {}
    explicit SignedBigInt(LL num) : absVal(std::abs(num)), is_minus(num < 0) {}
    explicit SignedBigInt(const string& num) {
        if(!isdigit(num[0])) {
            is_minus = (num[0] == '-');
            absVal = num.c_str() + 1;
        } else {
            is_minus = false;
            absVal = num;
        }
    }
    explicit SignedBigInt(const UnsignedBigInt& val) : absVal(val), is_minus(false) {}

    explicit operator int() {
        return is_minus ? -(int)absVal : (int)absVal;
    }
    explicit operator double() const {
        return is_minus ? -(double)absVal : (double)absVal;
    }
    explicit operator string() const {
        string ans;
        if (absVal.s.empty()) {
            ans = '0';
        } else {
            if (is_minus)
                ans += '-';
            ans += (string)absVal;
        }
        return ans;
    }
    explicit operator bool() const {
        return !absVal.s.empty();
    }
    explicit operator int() const {
        return absVal.s.empty() ? 0 : (is_minus ? -absVal.s[0] : absVal.s[0]);
    }

    SignedBigInt& operator = (const int num) {
        return (*this = SignedBigInt(num));
    }
    SignedBigInt& operator = (const string& num) {
        return (*this = SignedBigInt(num));
    }

    bool operator == (const SignedBigInt& b) const
    {
        return absVal.s.empty() && b.absVal.s.empty() ? 1 : (is_minus != b.is_minus ? 0 : absVal == b.absVal);
    }
    bool operator < (const SignedBigInt& b) const
    {
        return absVal.s.empty() && b.absVal.s.empty() ? 0 : (is_minus != b.is_minus ? is_minus : (is_minus ? b.absVal < absVal : absVal < b.absVal));
    }
    bool operator <= (const SignedBigInt& b) const {
        return *this < b || *this == b;
    }
    bool operator > (const SignedBigInt& b) const {
        return b < *this;
    }
    bool operator >= (const SignedBigInt& b) const {
        return b <= *this;
    }
    bool operator != (const SignedBigInt& b) const {
        return !(*this == b);
    }

    bool operator == (int b) const {
        return (b < 0) ^ is_minus ? (absVal.s.empty() && b == 0) : absVal == UnsignedBigInt(std::abs(b));
    }
    bool operator < (int b) const
    {
        return absVal.s.empty() ? b > 0 : ((b < 0) ^ is_minus ? is_minus : (is_minus ? -b < absVal : absVal < b));
    }
    bool operator <= (int rhs) const {
        return *this < rhs || *this == rhs;
    }
    bool operator > (int rhs) const {
        return !(*this <= rhs);
    }
    bool operator >= (int rhs) const {
        return !(*this < rhs);
    }
    bool operator != (int rhs) const {
        return !(*this == rhs);
    }

    SignedBigInt& AddEq(bool b_is_minus, const UnsignedBigInt& b_absVal)
    {
        if(is_minus ^ b_is_minus)//different sign
        {
            if(absVal < b_absVal)
            {
                absVal = b_absVal - absVal;
                is_minus = b_is_minus;
            }
            else
                absVal -= b_absVal;
        }
        else
            absVal += b_absVal;
        return *this;
    }
    SignedBigInt& operator += (const SignedBigInt& b)
    {
        return AddEq(b.is_minus, b.absVal);
    }
    SignedBigInt operator + (const SignedBigInt& b) const
    {
        SignedBigInt ans = *this;
        return ans += b;
    }

    //SignedBigInt& AddEq(bool b_is_minus, const UnsignedBigInt& b_absVal)
    SignedBigInt& operator -= (const SignedBigInt& b)
    {
        return AddEq(!b.is_minus, b.absVal);
    }
    SignedBigInt operator - (const SignedBigInt& b) const {
        return SignedBigInt(*this) -= b;
    }

    SignedBigInt operator - () const
    {
        SignedBigInt ans;
        ans.is_minus = !is_minus;
        ans.absVal = absVal;
        return ans;
    }

    SignedBigInt operator * (const SignedBigInt& b) const
    {
        SignedBigInt ans;
        ans.is_minus = is_minus ^ b.is_minus;
        ans.absVal = absVal * b.absVal;
        return ans;
    }
    SignedBigInt& operator *= (const SignedBigInt& b)
    {
        return *this = *this * b;
    }

    SignedBigInt operator / (const SignedBigInt& b) const
    {
        SignedBigInt ans;
        ans.is_minus = is_minus ^ b.is_minus;
        ans.absVal = absVal / b.absVal;
        return ans;
    }
    SignedBigInt& operator /= (const SignedBigInt& b)
    {
        return *this = *this / b;
    }

    SignedBigInt operator % (const SignedBigInt& b) const
    {
        SignedBigInt ans;
        ans.is_minus = is_minus;
        ans.absVal = absVal % b.absVal;
        return ans;
    }
    SignedBigInt& operator %= (const SignedBigInt& b)
    {
        return *this = *this % b;
    }

    SignedBigInt abs() const {
        return SignedBigInt(absVal);
    }

    SignedBigInt& operator += (int rhs) {
        if (is_minus ^ (rhs<0)) {
            if (absVal >= rhs) {
                absVal -= rhs;
            } else {
                absVal = UnsignedBigInt(rhs - absVal);
                is_minus = !is_minus;
            }
        } else {
            absVal += rhs;
        }
        return *this;
    }
    SignedBigInt& operator ++ () {
        return *this += 1;
    }
    SignedBigInt operator + (int rhs) {
        SignedBigInt ans = *this;
        return ans += rhs;
    }

    SignedBigInt& operator -= (int rhs) {
        if (rhs >= 0) {
            if (is_minus) {
                absVal += rhs;
            } else {
                absVal -= rhs;
            }
        } else {
            absVal += -rhs;
        }
        return *this;
    }
    SignedBigInt& operator -- () {
        return *this -= 1;
    }
    SignedBigInt operator - (int rhs) {
        SignedBigInt ans = *this;
        return ans -= rhs;
    }

    SignedBigInt& operator *= (int rhs) {
        if (rhs < 0) {
            is_minus = !is_minus;
            rhs = -rhs;
        }
        absVal *= rhs;
        return *this;
    }
    SignedBigInt operator * (int rhs) {
        SignedBigInt ans = *this;
        return ans *= rhs;
    }

    SignedBigInt& operator /= (int rhs) {
        assert(rhs);
        if (rhs < 0) {
            is_minus = !is_minus;
            rhs = -rhs;
        }
        absVal /= rhs;
        return *this;
    }
    SignedBigInt operator / (int rhs) {
        SignedBigInt ans = *this;
        return ans /= rhs;
    }

    int operator % (int rhs) {
        int ans = absVal % std::abs(rhs);
        return is_minus ? -ans : ans;
    }

    SignedBigInt& operator %= (int rhs) {
        absVal %= std::abs(rhs);
        return *this;
    }
};

ostream& operator << (ostream& out, const SignedBigInt& a)
{
    return out << string(a);
}

istream& operator >> (istream& in, SignedBigInt& a)
{
    string str;
    if (in >> str)
        a = str;
    return in;
}

SignedBigInt sqrt(const SignedBigInt& x, int m) {
    assert(!x.is_minus);
    return SignedBigInt(sqrt(x.absVal, m));
}

