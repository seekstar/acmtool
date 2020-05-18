struct EDGE {
	int from, to, next;
	int cost, cap;
};
struct GRAPH_EDGES {
	const static int max_edge = 2 * MAXM, max_node = MAXN;
    EDGE edge[max_edge];
    int m, head[max_node], n;
    void Init(int _n) {
        m = 0;
        n = _n + 1;
        memset(head, -1, n * sizeof(int));
    }
    void AddDi(int u, int v, int cost, int cap) {
        edge[m] = EDGE{u, v, head[u], cost, cap};
        head[u] = m++;
    }
    void AddUndi(int u, int v, int cost, int cap) {
        AddDi(u, v, cost, cap);
        AddDi(v, u, cost, cap);
    }
};

