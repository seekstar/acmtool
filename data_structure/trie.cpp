#define MAXDICT 26
template<typename T>
struct TrieNode
{
    typedef T CntType;
    const static int DictLen = MAXDICT;
    TrieNode* c[MAXDICT];
    CntType v;
    TrieNode(CntType initV = 0)
    {
        v = initV;
        memset(c, 0, sizeof(c));
    }
};
template<typename NodeType, typename DictType>
struct TRIE
{
    typedef typename NodeType::CntType CntType;

    NodeType root;

    TRIE(){}
    void insert(DictType arr[], int len)
    {
        NodeType* cur = &root;
        for(int i = 0; i < len; i++) {
            if(NULL == cur->c[arr[i]])
                cur->c[arr[i]] = new NodeType;
            cur = cur->c[arr[i]];
            ++cur->v;
        }
    }

    CntType query(DictType arr[], int len)
    {
        int i;
        NodeType* cur = &root;
        for(i = 0; i < len && cur->c[arr[i]]; cur = cur->c[arr[i++]]);

        return i == len ? cur->v : 0;
    }
};
