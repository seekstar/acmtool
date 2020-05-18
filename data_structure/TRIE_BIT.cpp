#define MAX_NODE_TRIE (50 * MAXN)
struct TRIE_BIT {
	int c[MAX_NODE_TRIE][2];        //1 is the root. 0 is invalid
	int n;

	void Init() {
		n = 1;
		c[1][0] = c[1][1] = 0;
	}
	void Insert(uint32_t v)
	{
	    int now = 1;
		for (int i = 0; i < 32; ++i) {
			if (0 == c[now][v >> 31]) {
				c[now][v >> 31] = (++n);
				now = c[now][v >> 31];
				c[now][0] = c[now][1] = 0;
			} else {
                now = c[now][v >> 31];
			}
			v <<= 1;
		}
	}
	uint32_t Query_max_xor(uint32_t v)
	{
		uint32_t ans = 0;
		int now = 1;
		for (int i = 0; i < 32; ++i) {
			ans <<= 1;
			if (c[now][1 - (v >> 31)]) {
				now = c[now][1 - (v >> 31)];
				ans |= (1 - (v >> 31));
			} else {
				now = c[now][v >> 31];
				ans |= (v >> 31);
			}
			v <<= 1;
		}
		return ans;
	}
};
