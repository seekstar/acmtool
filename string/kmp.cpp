template<typename ElemType>
int kmp(ElemType s[], int m, ElemType p[], int n, int fail[]) {
	int cnt = 0, j = 0;
	for(int i = 0; i < m; i++) {
		while(j != -1 && s[i] != p[j])
			j = fail[j];
		if(++j == n) {
			++cnt;
			j = fail[j];
		}
	}
	return cnt;
}

//The length of fail will be (n+1)
template<typename ElemType>
void GetFail(int fail[], int n, ElemType p[]) {
	int i = 0, k = -1;
	fail[0] = -1;
	while(i < n)
		if(k == -1 || p[i] == p[k])
			fail[++i] = ++k;
		else
			k = fail[k];
}

