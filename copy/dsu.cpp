vector<int> rank, root;

int find(int x) {
    if (x == root[x]) return x;
    return root[x] = find(root[x]);
}
bool un(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return false;
    if (rank[x] < rank[y]) swap(x, y);
    root[y] = x;
    rank[x] += rank[y];
    return true;
}

void init(int n) {
    rank.assign(n + 1, 1);
    root.resize(n + 1);
    for (int i = 0; i <= n; i++) root[i] = i;
}