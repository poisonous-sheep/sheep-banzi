#include <bits/stdc++.h>
using namespace std;
#define int long long

// Hopcroft-Karp 二分图最大匹配，O(E * sqrt(V))。
// 左部编号 1..n1，右部编号 1..n2。支持重边，0 表示没有匹配。
struct HK {
    int n1, n2, shortest;
    vector<vector<int>> e;
    vector<int> ml, mr, dis, cur;

    void init(int _n1, int _n2) {
        n1 = _n1;
        n2 = _n2;
        e.assign(n1 + 1, {});
        ml.assign(n1 + 1, 0);
        mr.assign(n2 + 1, 0);
        dis.assign(n1 + 1, -1);
        cur.assign(n1 + 1, 0);
    }

    // 添加原图的边：左部 u -> 右部 v。
    void add(int u, int v) {
        e[u].push_back(v);
    }

    // 分层：从所有未匹配的左部点同时出发，求最短增广路长度。
    bool bfs() {
        queue<int> q;
        fill(dis.begin(), dis.end(), -1);
        shortest = LLONG_MAX;

        for (int i = 1; i <= n1; i++) {
            if (!ml[i]) {
                dis[i] = 0;
                q.push(i);
            }
        }

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (dis[u] >= shortest) continue;

            for (int v : e[u]) {
                int w = mr[v];
                if (!w) {
                    shortest = dis[u] + 1;
                } else if (dis[w] == -1) {
                    dis[w] = dis[u] + 1;
                    q.push(w);
                }
            }
        }
        return shortest != LLONG_MAX;
    }

    // 在当前分层图上递归 DFS，寻找最短增广路。
    // cur[u] 是当前弧，避免同一轮重复枚举无效边。
    bool dfs(int u) {
        for (int &i = cur[u]; i < (int)e[u].size(); i++) {
            int v = e[u][i];
            int w = mr[v];

            // v 未匹配，或它原来的搭档 w 能沿下一层找到新匹配。
            if ((!w && dis[u] + 1 == shortest) ||
                (w && dis[w] == dis[u] + 1 && dfs(w))) {
                ml[u] = v;
                mr[v] = u;
                return true;
            }
        }
        dis[u] = -1;  // 当前 u 找不到增广路，剪枝
        return false;
    }

    // 返回当前图的最大匹配数；重复调用不会重复累计。
    int matching() {
        int ans = 0;
        for (int i = 1; i <= n1; i++) ans += (ml[i] != 0);
        while (bfs()) {
            fill(cur.begin(), cur.end(), 0);
            for (int i = 1; i <= n1; i++) {
                if (!ml[i] && dfs(i)) ans++;
            }
        }
        return ans;
    }
};

// 用法示例：给定 n1, n2, m，求二分图最大匹配并输出选中的匹配边。
// 如有多组测试，每组都重新 init。
void solve() {
    int n1, n2, m;
    cin >> n1 >> n2 >> m;
    HK hk;
    hk.init(n1, n2);
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        hk.add(u, v);
    }
    cout << hk.matching() << '\n';

    // 查询匹配关系：
    // hk.ml[u] 是左部点 u 匹配的右部点；hk.mr[v] 反之。
    // for (int u = 1; u <= n1; u++) {
    //     if (hk.ml[u]) cout << u << " " << hk.ml[u] << '\n';
    // }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    // cin >> t;
    while (t--) solve();
    return 0;
}
