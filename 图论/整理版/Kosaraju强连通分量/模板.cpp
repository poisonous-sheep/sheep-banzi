#include <bits/stdc++.h>
using namespace std;
#define int long long

// Kosaraju强连通分量：有向图强连通分量划分与缩点；支持重边、自环及不连通图。
// O(n+m)时间与空间，递归栈O(n)。
struct Kosaraju {
    // 以下顶点表均由init按n+1项assign重建；顶点下标1..n，0号预留不用。
    // 内层邻接位置从0开始，init清空旧边；标记/时间戳/归属表清0。
    int n;   // 原图顶点数；编号 1..n。
    int cnt; // 已求 SCC 数，0..n；第二遍发现一个新分量时加 1。
    // e/erev：二维变长邻接表，分别存出边终点/入边起点；下标 1..n；init clear。
    // 每个邻接表的位置从 0 开始；允许重边、自环。
    vector<vector<int>> e, erev;
    // vis：一维访问标记，下标 1..n，值 0/1；init 清 0，两遍 DFS 之间必须再次清 0。
    vector<int> vis;
    // bel：一维 SCC 编号，下标 1..n，值 1..cnt；init 清 0，第二遍赋值。
    vector<int> bel;
    // out：一维退出序，out[j] 为第 j 个退出的顶点，j=0..n-1；init clear。
    vector<int> out;
    // c：一维当前 SCC 顶点表，每次 dfs2 前 clear；最多 n 项。
    vector<int> c;
    // scc：二维 SCC 表，scc[k-1] 存第 k 个分量；init clear；总成员数 n。
    vector<vector<int>> scc;

    // init(n_)：初始化点数与全部容器；返回 void；前提 n_>=1；首次初始化时间O(n_)；复用对象还需销毁旧图的邻接元素。
    void init(int n_) {
        n = n_;
        cnt = 0;
        out.clear();
        c.clear();
        scc.clear();
        e.assign(n + 1, {});
        erev.assign(n + 1, {});
        vis.assign(n + 1, 0);
        bel.assign(n + 1, 0);
    }
    // dfs(u)：原图 DFS；u 为未访问顶点；返回 void；退出时写入 out。
    // 前提：图已建好，vis[u]==0；整遍 O(n+m)。
    void dfs(int u) {
        vis[u] = 1;
        for (int v : e[u])
            if (!vis[v])
                dfs(v); // v：原图出边终点，1..n。
        out.push_back(u);
    }
    // dfs2(u)：反图 DFS；u 为未访问顶点；返回 void；收集一个 SCC 到 c。
    // 前提：第一遍已完成，vis 已清 0，cnt 已增加；整遍 O(n+m)。
    void dfs2(int u) {
        vis[u] = 1;
        bel[u] = cnt;
        c.push_back(u);
        for (int v : erev[u])
            if (!vis[v])
                dfs2(v); // v：反图邻点，1..n。
    }
    // run()：无参数，返回 void；完成原图退出序和反图分量划分；时间 O(n+m)。
    // 前提：已 init；每条 u->v 同时加入 e[u] 和 erev[v]；只运行一次。
    void run() {
        for (int u = 1; u <= n; u++)
            if (!vis[u])
                dfs(u);
        for (int u = 1; u <= n; u++)
            vis[u] = 0;
        reverse(out.begin(), out.end());
        for (int u : out)
            if (!vis[u]) {
                ++cnt;
                c.clear();
                dfs2(u);
                scc.push_back(c);
            }
    }

    // addedge(u,v)：参数为有向边起终点1..n；返回void；前提已init且尚未run。
    // 作用：同时建立原图与反图；每次摊还O(1)。
    void addedge(int u, int v) {
        e[u].push_back(v);
        erev[v].push_back(u);
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    Kosaraju scc;
    scc.init(n);
    vector<pair<int, int>> e(m);
    for (auto &[u, v] : e) {
        cin >> u >> v;
        scc.addedge(u, v);
    }
    scc.run();
    vector<int> out(scc.cnt + 1), sz(scc.cnt + 1);
    for (int u = 1; u <= n; u++)
        sz[scc.bel[u]]++;
    for (auto [u, v] : e)
        if (scc.bel[u] != scc.bel[v])
            out[scc.bel[u]]++;
    int ans = 0, count = 0;
    for (int c = 1; c <= scc.cnt; c++)
        if (!out[c]) {
            count++;
            ans = sz[c];
        }
    cout << (count == 1 ? ans : 0) << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--)
        solve();
    return 0;
}
