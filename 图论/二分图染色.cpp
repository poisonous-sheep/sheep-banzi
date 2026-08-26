auto dfs = [&](auto&& dfs, int x) -> bool {
    // 枚举 x 的所有相邻点
    for (auto v : adj[x]) {

        // vis[v] == 3 表示 v 还没有被染色
        if (vis[v] == 3) {

            // 给 v 染成和 x 不同的颜色
            // 3 ^ 1 = 2
            // 3 ^ 2 = 1
            vis[v] = 3 ^ vis[x];

            // 继续向下 DFS
            // 如果下面发现不是二分图，直接返回 false
            if (!dfs(dfs, v)) return false;

        }
        // 如果 v 已经染过色，并且和 x 的颜色相同
        // 说明相邻两个点颜色相同，不满足二分图条件
        else if (vis[v] == vis[x]) {
            return false;
        }
    }

    // 没有发现冲突，说明当前这部分可以正常二分图染色
    return true;
};
