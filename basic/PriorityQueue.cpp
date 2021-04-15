template <typename T, size_t MAX_SIZE, typename Compare = less<T> >
class PriorityQueue {
	T s[MAX_SIZE]; // s[0] is not used
	size_t len;
	Compare cmp;
public:
	PriorityQueue() {
		len = 0;
	}
	bool empty() const {
		return len == 0;
	}
	size_t size() const {
		return len;
	}
	T top() const {
		return s[1];
	}
	void pop() {
		size_t cur = 1;
		while (1) {
			size_t left = cur << 1;
			if (left > len)
				break;
			size_t right = cur << 1 | 1;
			if (right <= len && cmp(s[right], s[left]))
				left = right;
			if (cmp(s[len], s[left]))
				break;
			s[cur] = s[left];
			cur = left;
		}
		s[cur] = s[len--];
	}
	void push(T x) {
		size_t cur = ++len;
		for (; cur >> 1 && cmp(x, s[cur >> 1]); cur >>= 1)
			s[cur] = s[cur >> 1];
		s[cur] = x;
	}
};
