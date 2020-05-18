int sg[LEN];
inline void InitSG(void)
{
	memset(sg, -1, sizeof(sg));
}
//Get sg[m]
int SG(int arr[], int len, int m)
{
	bool* record = new bool[m+1];
	int i;

	memset(record, 0, (m+1) * sizeof(bool));
	for(i = 0; i < len && arr[i] <= m; i++)
	{
		if(sg[m - arr[i]] == -1)
			sg[m - arr[i]] = SG(arr, len, m - arr[i]);
		record[sg[m - arr[i]]] = 1;
	}
	for(i = 0; record[i]; i++);

	delete record;

	return i;
}
