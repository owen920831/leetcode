#include <iostream>
#include <vector>
using namespace std;

class Fenwick {
    vector<int> tree;

public:
    Fenwick(int n) : tree(n) {}

    // 把下标为 i 的元素增加 v
    void add(int i, int v) {
        while (i < tree.size()) {
            tree[i] += v;
            i += i & -i;
        }
    }

    // 返回下标在 [1,i] 的元素之和
    int pre(int i) {
        int res = 0;
        while (i > 0) {
            res += tree[i];
            i &= i - 1;
        }
        return res;
    }
};