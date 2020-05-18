//arr should start at 0.It records that the stones that you can take.
//arr should be in ascending order
//n is the length of the required array
void GetSG(int sg[], int n, int arr[], int len)
{
    int i, j;
    bool* record = new bool[n];
    for(i = 0; i < n; i++)//i is the number of stones at present
    {
        memset(record, 0, n * sizeof(bool));
        for(j = 0; j < len && i >= arr[j]; j++)
            record[sg[i - arr[j]]] = 1;
        for(j = 0; j < n && record[j]; j++);

        sg[i] = j;
    }
    delete record;
}
