void PrintTree(int rt, string& str, int(PrintNode)(T)) {
        int rec = str.length();
        int len;
        if (rt) {
            len = PrintNode(keys[rt]);
            printf("---");
            str.append(len, ' ');
            str.append(" | ");
            PrintTree(ls(rt), str, PrintNode);
            printf("%s\n", str.c_str());
            str[str.length()-1] = str[str.length()-2] = '-';
            printf("%s", str.c_str());

            str[str.length()-1] = str[str.length()-2] = ' ';
            PrintTree(rs(rt), str, PrintNode);

            str.resize(rec);
        } else {
            puts("/\\");
        }
    }
    void PrintTree(int rt, int(PrintNode)(T)) {
        string str;
        PrintTree(rt, str, PrintNode);
    }
    void PrintBST(int(PrintNode)(T)) {
        PrintTree(root, PrintNode);
    }

    void Traverse(int rt, int path[], int& len) {
        if (rt) {
            Traverse(ls(rt), path, len);
            path[len++] = rt;
            Traverse(rs(rt), path, len);
        }
    }
    void Traverse(int path[], int& len) {
        Traverse(root, path, len);
    }
    void Print() {
        static int path[MAXN];
        int len = 0;
        Traverse(path, len);
        for (int i = 0; i < len; ++i) {
            PrintNode(keys[path[i]]);
        }
        putchar('\n');
    }
