# Kruskal 重构树板子：最小化路径最大边权

> 以「给定无向带权图，多次询问两点之间路径的最大边权最小能是多少」为模板。代码沿用你写的 `Edge / adj / fid / val / dist / pre`，只修正粘贴产生的 lambda 参数尖括号。

## 一、这题在求什么

对每个询问 `u, v`，在所有从 `u` 到 `v` 的路径里，找路径上**最大边权的最小值**：

\[
\min_{P:u\leadsto v}\ \max_{e\in P} w_e
\]

如果两个点不连通，输出 `impossible`。

例如 `1 → 2 → 3` 的边权依次是 `2, 5`，这条路径的最大边权是 `5`。我们要在所有可选路径里让这个最大值尽量小。

## 二、为什么要建 Kruskal 重构树

把边按权值**从小到大**加入。对于当前边 `(u, v, w)`：

- 如果 `u, v` 已经处于同一连通块，这条边不用处理。
- 如果它们属于不同连通块，就新建一个点 `tot`，令 `val[tot] = w`，把两个连通块对应的树根 `fu, fv` 接到 `tot` 下面。

一次成功合并长这样：

```text
        tot，val[tot] = w
          /          \
         fu          fv
```

`1 ~ n` 是原图节点，作为叶子；`n+1 ~ tot` 是每次合并创建的节点。成功合并最多 `n-1` 次，因此重构树最多有 `2n-1` 个节点。

**关键含义：**新节点 `tot` 表示这两个连通块在处理权值 `w` 的边时第一次连通。并查集也要让 `tot` 成为新连通块的代表，所以代码写的是 `fid[fu] = fid[fv] = tot`。

## 三、查询为什么是 `val[lca(u, v)]`

设 `z = lca(u, v)`。在重构树上，`u` 与 `v` 分处 `z` 的两棵儿子子树。创建 `z` 之前，它们尚未连通；创建 `z` 时，它们首次连通，此时处理的边权恰好是 `val[z]`。

因此：

\[
\boxed{\displaystyle
\min_{P:u\leadsto v}\max_{e\in P}w_e
=\operatorname{val}\bigl(\operatorname{LCA}(u,v)\bigr)}
\]

边权相同时，排序中同权边的先后合并顺序可能不同，但首次连通的**权值**相同，答案不会受影响。

## 四、按你的写法整理的完整代码

```cpp
#include <bits/stdc++.h>
#include <vector>

using namespace std;

#define int long long

// 原图 n 个点，重构树最多 2n-1 个点。
// 这里的 N = 4e5+10 适用于 n <= 2e5。
const int N = 4e5 + 10;

struct Edge {
    int u, v, w;
};

vector<int> adj[N];  // 重构树：父节点 -> 两个儿子
int fid[N];          // 并查集；代表元是当前连通块的重构树根
int val[N];          // 新建节点的权值，即造成合并的边权

int root(int x) {
    if (fid[x] == x) return x;
    return fid[x] = root(fid[x]);
}

void solve() {
    int n, m;
    cin >> n >> m;

    vector<Edge> e(m);
    for (auto& [u, v, w] : e) {
        cin >> u >> v >> w;
    }

    // 最小化路径最大边权：边从小到大加入。
    sort(e.begin(), e.end(), [](Edge a, Edge b) {
        return a.w < b.w;
    });

    int tot = n;  // 1~n 是原图点，新点从 n+1 开始
    for (int i = 1; i <= 2 * n; i++) {
        fid[i] = i;
    }

    // Kruskal 建重构树
    for (auto [u, v, w] : e) {
        int fu = root(u);
        int fv = root(v);
        if (fu == fv) continue;  // 已经连通，不产生新节点

        ++tot;
        val[tot] = w;

        // 新节点作为原来两个连通块树根的父亲
        adj[tot].push_back(fu);
        adj[tot].push_back(fv);

        // 并查集的新代表元是 tot
        fid[fu] = tot;
        fid[fv] = tot;
        fid[tot] = tot;
    }

    // LCA 的数组要按 tot 开，不能只按 n 开。
    vector<int> dist(tot + 1, 0);
    vector<vector<int>> pre(tot + 1, vector<int>(26));
    dist[0] = -1;

    // 这里仅把粘贴时的 <auto&& ...> 改为合法的 lambda 参数语法。
    auto dfs = [&](auto&& dfs, int u, int fa) -> void {
        dist[u] = dist[fa] + 1;
        pre[u][0] = fa;

        // adj 只存父 -> 子，实际不会遍历到父亲。
        for (auto v : adj[u]) {
            if (v == fa) continue;
            dfs(dfs, v, u);
        }
    };

    // 原图可能不连通，最终得到的是多棵重构树。
    // fid[i] == i 的点就是其中一棵树的根。
    for (int i = 1; i <= tot; i++) {
        if (fid[i] == i) {
            dfs(dfs, i, 0);
        }
    }

    // 预处理 2^i 级祖先；pre[0][i] 默认为 0。
    for (int i = 1; i <= 20; i++) {
        for (int j = 1; j <= tot; j++) {
            pre[j][i] = pre[pre[j][i - 1]][i - 1];
        }
    }

    // 同样仅修正粘贴时的 <int x, int y>。
    auto lca = [&](int x, int y) {
        if (dist[x] < dist[y]) swap(x, y);

        // 让较深的 x 跳到 y 的深度。
        // dist[0] = -1，保证不会误跳到虚点 0。
        for (int i = 20; i >= 0; i--) {
            if (dist[pre[x][i]] >= dist[y]) {
                x = pre[x][i];
            }
        }
        if (x == y) return x;

        // 一起往上跳，停在 LCA 的两个不同儿子。
        for (int i = 20; i >= 0; i--) {
            if (pre[x][i] != pre[y][i]) {
                x = pre[x][i];
                y = pre[y][i];
            }
        }
        return pre[x][0];
    };

    int q;
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;

        // 不在同一个最终连通块，就不存在路径。
        if (root(u) != root(v)) {
            cout << "impossible\n";
            continue;  // 只跳过当前询问
        }

        cout << val[lca(u, v)] << endl;
    }
}

signed main() { solve(); }
```

## 五、把代码分成三段记

1. **建树：**边权升序；每次成功合并，创建权值为当前边权的新父节点。
2. **预处理：**每棵重构树各做一次 DFS，求 `dist` 和 `pre`。
3. **回答：**先用 `root(u) != root(v)` 判断是否连通；连通时输出 `val[lca(u, v)]`。

## 六、你这份板子的边界

- `N = 4e5+10` 与 `pre` 跳到第 20 层，针对 `n <= 2e5` 足够；换更大的数据范围时，`N` 和倍增层数都要随之调整。
- `dfs` 保留了你的递归写法。重构树可能退化成很深的链，如果评测环境栈较小且 `n` 接近上限，可能出现递归栈溢出。
- 如果询问 `u == v`，`lca(u,u)=u`；原图点的 `val[u]` 默认为 `0`。若题目对同点询问有其他定义，应按题意单独处理。

