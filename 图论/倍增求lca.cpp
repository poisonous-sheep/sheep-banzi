// --- LCA 相关变量 ---
int dist[N];            // 存储每个节点的深度
vector<int> egde[N];    // 邻接表存图
int pre[N][26];         // 倍增表：pre[u][i] 表示节点 u 向上跳 2^i 步到达的祖先

// DFS 预处理：计算深度和每个节点的直接父节点 (2^0)
void dfs(int u, int fa) {
    dist[u] = dist[fa] + 1; // 当前深度 = 父节点深度 + 1
    pre[u][0] = fa;         // 2^0 级祖先就是父节点
    for (auto v : egde[u]) {
        if (v != fa) dfs(v, u); // 避免跑回父节点导致死循环
    }
}

// 最近公共祖先查询函数
int lca(int x, int y) {
    // 1. 确保 x 是深度较深的那个点
    if (dist[x] < dist[y]) swap(x, y);

    // 2. 利用倍增将 x 向上跳，跳到与 y 同一深度
    for (int i = 20; i >= 0; i--) {
        // 如果 x 跳了 2^i 层后深度仍不小于 y，则执行跳跃
        if (dist[pre[x][i]] >= dist[y]) {
            x = pre[x][i];
        }
    }

    // 3. 如果跳到同一高度后两者相等，说明 y 就是 x 的祖先
    if (x == y) return x;

    // 4. x 和 y 同时向上跳，尽可能跳到 LCA 的下一层
    for (int i = 20; i >= 0; i--) {
        // 如果跳 2^i 步后两者祖先不同，说明还没跳到或跳过头，执行跳跃
        if (pre[x][i] != pre[y][i]) {
            x = pre[x][i];
            y = pre[y][i];
        }
    }

    // 5. 循环结束时，x 和 y 就在 LCA 的正下方，它们的父节点就是 LCA
    return pre[x][0];
}

void solve() {
    int n, m, s;
    if (!(cin >> n >> m >> s)) return;

    // 1. 建图：读入 n-1 条边构成树
    rep(1, n - 1) {
        int u, v;
        cin >> u >> v;
        egde[u].push_back(v);
        egde[v].push_back(u);
    }

    // 2. 预处理：从根节点 s 开始 DFS
    dfs(s, 0);

    // 3. 动态规划填充倍增表
    // 状态转移：跳 2^i 步 = 先跳 2^(i-1) 步，再跳 2^(i-1) 步
    for (int i = 1; i <= 20; i++) {
        for (int j = 1; j <= n; j++) {
            if (pre[j][i - 1]) {
                pre[j][i] = pre[pre[j][i - 1]][i - 1];
            }
        }
    }

    // 4. 处理 m 次询问
    while (m--) {
        int u, v;
        cin >> u >> v;
        cout << lca(u, v) << endl;
    }
}
