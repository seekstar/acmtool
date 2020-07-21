#define BUF 30000011
char Buf[BUF], *buf = Buf;
template <typename T>
inline void uread(T& a) {
    for (a = 0; *buf < 48; ++buf);
    while (*buf > 47)
        a = a * 10 + *buf++ - '0';
}
//fread(Buf, 1, BUF, stdin);
template<typename T>
void read(T& x) {
    x = 0;
    bool neg = 0;
    char c;
    while(!isdigit(c=getchar()))
        if(c == '-') neg = 1;
    do {
        x = x * 10 + c - '0';
    } while (isdigit(c=getchar()));
    if(neg) x = -x;
}

template<typename T>
void output(T x) {
    static char buf[100];
    static int t;
    if(x < 0) {
        putchar('-');
        x = -x;
    }
    do {
        buf[t++] = x % 10 + '0';
    } while(x /= 10);
    while(t) putchar(buf[--t]);
}




struct IO {
    const static int IN_LEN = 100000, OUT_LEN = 100000, goodbit = 0, eof = EOF;
    char buf[IN_LEN], pbuf[OUT_LEN], *p1, *p2, *pp, sta[111];
    int state;

    IO() {
        p1 = p2 = buf, pp = pbuf, state = goodbit;
    }
    ~IO() {
        finish();
    }
    inline char GetChar() {
        return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, IN_LEN, stdin), p1 == p2) ? (state = eof) : *p1++;
    }
    IO& operator >> (char& v) {
        v = GetChar();
        return *this;
    }

    template <typename T>
    IO& ReadInt(T& v) {
        char ch;
        v = 0;
        bool neg = false;
        while (!isdigit(ch = GetChar())) {
            if(EOF == ch) return *this;
            if ('-' == ch) neg = true;
        }
        do v = v * 10 + ch - 48; while (isdigit(ch = GetChar()));
        if (neg) v = -v;
        return *this;
    }
    IO& operator >> (int& v) {
        return ReadInt(v);
    }
    IO& operator >> (LL& v) {
        return ReadInt(v);
    }
    IO& operator >> (__int128& v) {
        return ReadInt(v);
    }

    IO& operator >> (char* s){
        char ch;
        while(!isspace(ch = GetChar()) && ch != EOF)
            *s++ = ch;
        *s = 0;
        return *this;
    }
    inline IO& getline(char* s){
        char ch;
        while((ch = GetChar()) != '\n' && ch != EOF)
            *s++ = ch;
        *s = 0;
        return *this;
    }

    void PutChar(char c) {
        if (pp - pbuf == OUT_LEN) fwrite(pbuf, 1, OUT_LEN, stdout), pp = pbuf;
        *pp++ = c;
    }
    IO& operator << (char c){
        PutChar(c);
        return *this;
    }

    template <typename T>
    IO& OutInt(T& x) {
        if (x < 0) x = -x, PutChar('-');
        int top = 0;
        do { sta[top++] = x % 10, x /= 10; } while (x);
        while (top) PutChar(sta[--top] + '0');
        return *this;
    }
    IO& operator << (int x) {
        return OutInt(x);
    }
    IO& operator << (LL x) {
        return OutInt(x);
    }

    IO& operator << (char* s) {
        while(*s) PutChar(*s++);
        return *this;
    }
    explicit operator bool() const {
        return state == goodbit;
    }
    void finish() {
        fwrite(pbuf, 1, pp - pbuf, stdout);
    }
}io;
#define endl '\n'
