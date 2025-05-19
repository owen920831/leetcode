//dijkstra
class Solution {
public:
    int minTimeToReach(vector<vector<int>>& g) {
        int dir[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
        int n = g.size(), m = g[0].size();
        vector<vector<int>> dp(n, vector<int>(m, INT_MAX));
        // dis, x, y
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;
        pq.push({0, 0, 0});
        while (!pq.empty()){
            auto [d, x, y] = pq.top(); pq.pop();
            if (d > dp[x][y]) continue;
            for (auto [dx, dy]:dir){
                int nx = x + dx, ny = y + dy;
                if (0 <= nx && nx < n && 0 <= ny && ny < m) {
                    int new_dis = max(d, g[nx][ny]) + (nx+ny+1)%2 + 1;
                    if (new_dis < dp[nx][ny]) {
                        dp[nx][ny] = new_dis;
                        pq.push({new_dis, nx, ny});
                    }
                }
            }
        }
        return dp[n-1][m-1];
    }
};
// 0-1 bfs
class Solution {
    static constexpr int DIRS[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
public:
    bool findSafeWalk(vector<vector<int>>& grid, int health) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> dis(m, vector<int>(n, INT_MAX));
        dis[0][0] = grid[0][0];
        deque<pair<int, int>> q;
        q.emplace_front(0, 0);
        while (true) {
            auto [i, j] = q.front();
            q.pop_front();
            if (dis[i][j] >= health) {
                return false;
            }
            if (i == m - 1 && j == n - 1) {
                return true;
            }
            for (auto& [dx, dy] : DIRS) {
                int x = i + dx, y = j + dy;
                if (0 <= x && x < m && 0 <= y && y < n) {
                    int cost = grid[x][y];
                    if (dis[i][j] + cost < dis[x][y]) {
                        dis[x][y] = dis[i][j] + cost;
                        cost == 0 ? q.emplace_front(x, y) : q.emplace_back(x, y);
                    }
                }
            }
        }
    }
};