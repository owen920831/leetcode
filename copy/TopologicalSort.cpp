class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        if(n == 1) return {0};
        vector<vector<int>> g(n);
        vector<int> in(n, 0);
        for (auto e:edges){
            in[e[0]]++;
            in[e[1]]++;
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }
        queue<int> q;
        for (int i = 0; i < n; i++){
            if (in[i] == 1) q.push(i);
        }
        vector<int> res;
        while (!q.empty()){
            int sz = q.size();
            res.clear();
            for (int s = 0; s < sz; s++){
                int p = q.front(); q.pop();
                res.push_back(p);
                for (auto v:g[p]){
                    in[v]--;
                    if (in[v] == 1)
                        q.push(v);
                }
            }
        }
        return res;
    }
};