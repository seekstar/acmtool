//The shortest way using A_star
struct ASTAR_NODE{
	int f, g;
	int id;
	bool operator < (const ASTAR_NODE& rhs) const{
		return f > rhs.f;
	}
};
const int INF = 0x3f3f3f3f;
int AStar(const GRAPH_EDGES& graph, int s, int t){
	priority_queue<ASTAR_NODE> pq;
	static int h[MAX_NODE];	//expected
	const int& n = graph.n - 1;
	static int dist[MAX_NODE];  //dist[u] is the minimum f(v). If a f(v) is larger than it, then there is no need to push the f(v) into pq, because there is already a better one in pq.

	memset(dist, 0x3f, (n+1) * sizeof(dist[0]));
	memset(h, 0x3f, (n + 1) * sizeof(h[0]));
	for(int u = 1; u <= n; ++u){
		for(int e = graph.head[u]; ~e; e = graph.edge[e].next){
			h[u] = min(h[u], graph.edge[e].cost);
		}
	}
	h[t] = 0;
	dist[s] = 0;
	pq.push(ASTAR_NODE{h[s], 0, s});
	while(!pq.empty()){
		s = pq.top().id;
		int g_u = pq.top().g;
		pq.pop();
		if(s == t)return g_u;
		for(int e = graph.head[s]; ~e; e = graph.edge[e].next){
			int g = g_u + graph.edge[e].cost;
			int v = graph.edge[e].to;
			if(dist[v] > g + h[v]){
				dist[v] = g + h[v];
				pq.push(ASTAR_NODE{g + h[v], g, v});
			}
		}
	}
	return INF;
}



//The K-th shortest way using A_star. h[i] <= dist[i]. dist[i] is the minimum distance from i to t
//simple version
const int INF = 0x3f3f3f3f;
template<typename DistType>
struct ASTAR_NODE{
	DistType f, g;
	int id;
	bool operator < (const ASTAR_NODE& rhs) const{
		return f > rhs.f;
	}
};
template<typename DistType>
LL AStar(const GRAPH_EDGES& graph, int s, int t, DistType h[], int k){
	priority_queue<ASTAR_NODE<DistType> > pq;

	if(h[t] == numeric_limits<DistType>::max())return -1;
	if(s == t)++k;      // s can't get to itself directly
	pq.push(ASTAR_NODE<DistType>{h[s], 0, s});
	while(!pq.empty()){
		s = pq.top().id;
		DistType g_u = pq.top().g;
		pq.pop();
		if(s == t){
            --k;
            if(0 == k) return g_u;
        }
		for(int e = graph.head[s]; ~e; e = graph.edge[e].next){
			DistType g = g_u + graph.edge[e].cost;
			int v = graph.edge[e].to;
            pq.push(ASTAR_NODE<DistType>{g + h[v], g, v});
		}
	}
	return -1;
}

