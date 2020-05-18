#define MAX_BUCKET 0x100
template<typename T>
void RadixSort(T base[], int n){
	const int max_bit = 8 * sizeof(T);
	const int MASK = MAX_BUCKET-1;

	static T buffer[MAX_LENGTH];
	static T t[MAX_LENGTH];
    static T sa[MAX_LENGTH];	//sa[i] is the index of the i_th smallest number
    static T c[MAX_BUCKET];

	T *a = base, *b = buffer;
	for(int k = 0; k < max_bit; k += 8){
		memset(c, 0, sizeof(c));
		for(int i = 0; i < n; ++i){
			t[i] = (a[i] >> k) & MASK;
			++c[t[i]];
		}
		for(int i = 1; i < MAX_BUCKET; ++i)
			c[i] += c[i-1];
		for(int i = n-1; i >= 0; --i)
			sa[--c[t[i]]] = i;
		for(int i = 0; i < n; ++i)
			b[i] = a[sa[i]];
		swap(a, b);
    }
    if(a != base)
		memcpy(base, a, n * sizeof(T));
}
