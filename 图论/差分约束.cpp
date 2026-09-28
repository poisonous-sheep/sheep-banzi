#include <bits/stdc++.h>

#include <queue>
#include <vector>

using namespace std;

#define int long long
using pii = array<int, 2>;

const int INF = 1e18;

void solve() {
    int n, m;
    cin >> n >> m;

    /*
        差分约束：

        我们统一把所有限制转化为：

            x[v] >= x[u] + w

        那么就可以建一条边：

            u -> v，边权 w

        最后跑「最长路」。

        dis[i] 表示：
        根据当前所有约束，x[i] 至少需要取多大。

        因为题目要求：
            1. x[i] >= 0
            2. 每个 x[i] 尽可能小

        所以最终的最长路 dis[i]
        就是满足所有限制时 x[i] 的最小值。
    */

    // adj[u] 里面存 {v, w}
    // 表示存在约束：
    //
    // x[v] >= x[u] + w
    vector<vector<pii>> adj(n + 1);

    for (int i = 1; i <= m; i++) {
        int c, cp, y;
        cin >> c >> cp >> y;

        /*
            原限制：

                x[c] - x[cp] <= y

            移项：

                x[c] <= x[cp] + y

            但是我们要统一成：

                x[v] >= x[u] + w

            所以继续移项：

                x[cp] >= x[c] - y

            因此：

                u = c
                v = cp
                w = -y

            建边：

                c -> cp，权值 -y
        */

        adj[c].push_back({cp, -y});
    }

    /*
        题目还要求：

            x[i] >= 0

        我们建立一个超级源点 0，并令：

            x[0] = 0

        那么：

            x[i] >= x[0] + 0

        对应建边：

            0 -> i，权值 0

        这样所有变量初始至少都是 0。
    */
    for (int i = 1; i <= n; i++) {
        adj[0].push_back({i, 0});
    }

    /*
        最长路初始化：

        dis[i] 表示 x[i] 当前至少需要是多少。

        一开始除了超级源点之外都不知道，
        所以初始化为 -INF。

        超级源点：

            dis[0] = 0
    */
    vector<int> dis(n + 1, -INF);

    /*
        cnt[i]：
        表示当前得到 dis[i] 的这条最长路径
        一共经过了多少条边。

        用来判断是否存在正环。
    */
    vector<int> cnt(n + 1, 0);

    /*
        vis[i]：
        i 当前是否已经在 SPFA 队列中。
    */
    vector<int> vis(n + 1, 0);

    queue<int> q;

    // 超级源点初始化
    dis[0] = 0;

    q.push(0);
    vis[0] = 1;

    // ok = 0 表示出现正环，无解
    bool ok = 1;

    while (!q.empty() && ok) {
        int u = q.front();
        q.pop();

        // u 已经出队
        vis[u] = 0;

        for (auto [v, w] : adj[u]) {
            /*
                当前这条边表示：

                    x[v] >= x[u] + w

                而 dis[u] 是 x[u] 至少要达到的值。

                所以 x[v] 至少应该达到：

                    dis[u] + w

                如果：

                    dis[v] < dis[u] + w

                就说明现在的 dis[v] 太小，
                不满足这个约束，需要提高。
            */
            if (dis[v] < dis[u] + w) {
                dis[v] = dis[u] + w;

                /*
                    v 是从 u 转移过来的，
                    所以当前这条路径长度：

                        cnt[v] = cnt[u] + 1
                */
                cnt[v] = cnt[u] + 1;

                /*
                    为什么可以这样判正环？

                    图中总共有：

                        0, 1, 2, ..., n

                    一共 n + 1 个点。

                    如果不存在环，一条简单路径最多经过：

                        n 条边

                    如果某次最长路已经经过 >= n + 1 条边，
                    说明一定重复经过了某个点，
                    即出现了环。

                    而且这是「最长路」不断变大的过程中出现的环，
                    所以它是正环。

                    正环意味着：

                        x[a] >= x[a] + 正数

                    显然不可能满足。

                    所以整个差分约束系统无解。
                */
                if (cnt[v] >= n + 1) {
                    ok = 0;
                    break;
                }

                /*
                    如果 v 当前不在队列中，
                    就把它加入队列。

                    因为 dis[v] 变大之后，
                    v 可能继续影响它能到达的其他点。
                */
                if (!vis[v]) {
                    vis[v] = 1;
                    q.push(v);
                }
            }
        }
    }

    // 出现正环 -> 无解
    if (!ok) {
        cout << -1 << '\n';
        return;
    }

    /*
        dis[i] 就是：

            在满足所有限制的情况下，
            x[i] 能取得的最小非负值。
    */
    for (int i = 1; i <= n; i++) {
        cout << dis[i] << " \n"[i == n];
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
