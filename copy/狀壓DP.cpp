// 排列型(相鄰無關)
class Solution {
public:
    unordered_map<int, int> memo;
    int n, k;
    int dfs(vector<int>& strength, int vis){
        if ((1 << n) - 1 == vis) return 0;
        if (memo.count(vis)) return memo[vis];
        int res = INT_MAX;
        int x = 1 + k * (popcount((unsigned) vis));
        for (int j = 0; j < n; j++) {
            if ((vis >> j & 1) == 0) {
                res = min(res, dfs(strength, vis|(1 << j)) + (strength[j] - 1) / x + 1);
            }
        }
        memo[vis] = res;
        return res;
    }
    int findMinimumTime(vector<int>& strength, int K) {
        n = strength.size();
        k = K;
        return dfs(strength, 0);
    }
};

// 排列型(相鄰有關)
class Solution {
public:
    int specialPerm(vector<int>& nums) {
        int n = nums.size(), mod = 1e9+7;
        vector<vector<int>> f(1 << n, vector<int>(n+1, -1));
        auto dfs = [&](this auto&& dfs, int vis, int last) -> int {
            if (vis == (1 << n) - 1) return 1;
            int& res = f[vis][last];
            if (res != -1) return res;
            res = 0;
            for (int j = 0; j < n; j++) {
                if (last == 0 || ((vis >> j) & 1) == 0 && \
                    (nums[last-1] % nums[j] == 0 || nums[j] % nums[last-1] == 0)) {
                    res = (res % mod + dfs(vis | (1 << j), j+1) % mod) % mod;
                }
            }
            return res;
        };
        return dfs(0, 0);
    }
};

// 子集型狀壓dp
class Solution {
public:
    int distributeCookies(vector<int>& cookies, int k) {
        int n = cookies.size();
        int m = 1 << n; // 所有 subset 的總數
        // 預先計算所有 subset 的總和
        vector<int> subsetSum(m, 0);
        for (int mask = 0; mask < m; ++mask) {
            for (int i = 0; i < n; ++i) {
                if ((mask >> i) & 1) subsetSum[mask] += cookies[i];
            }
        }
        // memo[state][k] = 最小的最大值
        vector<vector<int>> memo(m, vector<int>(k + 1, -1));

        auto dfs = [&](auto&& dfs, int mask, int remain) -> int {
            if (mask == 0) return 0;             // 沒剩下任何 cookie
            if (remain == 0) return INT_MAX;     // 沒人可分了
            int& res = memo[mask][remain];
            if (res != -1) return res;
            res = INT_MAX;

            // 子集枚舉：枚舉 mask 的所有子集
            // 但只考慮 subset ⊆ mask
            for (int subset = mask; subset; subset = (subset - 1) & mask) {
                int unfair = max(subsetSum[subset], dfs(dfs, mask ^ subset, remain - 1));
                res = min(res, unfair);
                // ⚠️ 剪枝優化：如果 unfair 已經比 res 大了就可以跳過了
            }
            return res;
        };
        return dfs(dfs, m - 1, k);
    }
};