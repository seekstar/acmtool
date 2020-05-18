//得到树上某条边右侧的点数
//Need GRAPH_EDGES
int record[2*MAX][2];//record[i][0]指第i条边的from那一侧的点数（包括from），
void Init(int n)
{
	memset(record, -1, 2*n*sizeof(int[2]));
}
int rightPoint(int e)
{
    int toe;
    if(record[e][1] == -1)
    {
        record[e][1] = 1;
        for(toe = g.head[g.edge[e].to]; ~toe; toe = g.edge[toe].next)
        {
            if((toe^1) == e)continue;
            record[e][1] += rightPoint(toe);
        }
        record[e^1][0] = record[e][1];
        record[e^1][1] = record[e][0] = n - record[e][1];
    }
    return record[e][1];
}
