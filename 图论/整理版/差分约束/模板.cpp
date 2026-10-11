#include <bits/stdc++.h>
using namespace std;
#define int long long

// 差分约束：一般上界差分约束用Bellman-Ford判负环；非正权上界特例提供SCC+DAG最小正值变体。
// solve为O(nm)时间；minimum_positive为O(n+m)时间；空间O(n+m)。
struct SCC {
    // 以下顶点表均由init按n+1项assign重建；顶点下标1..n，0号预留不用。
    // 内层邻接位置从0开始，init清空旧边；标记/时间戳/归属表清0。
    int n;   // 顶点数，n>=1；顶点编号为 1..n。
    int idx; // DFS 时钟，范围 [0,n]；每首次访问一个点加 1。
    int cnt; // SCC 数，范围 [0,n]；按弹栈先后编号。

    // e：二维变长邻接表；e[u][j] 为 u 的第 j 条出边终点。
    // u=1..n，j=0..e[u].size()-1；init 中 clear；允许重边、自环。
    vector<vector<int>> e;
    // dfn：一维；dfn[u] 为首次访问时间，0 表示未访问；init 清 0；有效值 1..n。
    vector<int> dfn;
    // low：一维；low[u] 为子树按 Tarjan 规则能追溯到的最早未封闭时间戳。
    // 下标 1..n；init 清 0；首次访问置 dfn[u]，随后取 min。
    vector<int> low;
    // ins：一维；ins[u] 为 u 是否仍在 Tarjan 栈中；init 清0，标记取0/1，入栈置 true，弹栈置 false。
    vector<int> ins;
    // bel：一维；bel[u] 为 SCC 编号 1..cnt；init 清 0；0 表示尚未分配。
    vector<int> bel;
    // stk：一维栈，元素为顶点编号 1..n；init 弹空；最多存 n 个点。
    stack<int> stk;
    // scc：二维变长表；scc[c-1] 为 SCC c 的全部原图顶点；init clear；总成员数 n。
    vector<vector<int>> scc;

    // init(n_)：参数为顶点数；返回 void；清图和 Tarjan 状态。
    // 前提：n_>=1，下一步重新加边；首次初始化时间O(n_)；复用对象还需销毁旧图的邻接元素。
    void init(int n_) {
        n = n_;
        idx = cnt = 0;
        e.assign(n + 1, {});
        dfn.assign(n + 1, 0);
        low.assign(n + 1, 0);
        ins.assign(n + 1, 0);
        bel.assign(n + 1, 0);
        while (!stk.empty())
            stk.pop();
        scc.clear();
    }

    // dfs(u)：u 为当前顶点；返回 void；递归求 SCC 并填写 bel、scc。
    // 前提：图已建好，dfn[u]==0；一次 DFS 为 O(所访问顶点+扫描边)，全图 O(n+m)。
    void dfs(int u) {
        dfn[u] = low[u] = ++idx;
        ins[u] = true;
        stk.push(u);
        for (int v : e[u]) { // v：出边终点，范围 1..n。
            if (!dfn[v]) {
                dfs(v);
                low[u] = min(low[u], low[v]);
            } else if (ins[v]) {
                low[u] = min(low[u], dfn[v]);
            }
        }
        if (dfn[u] == low[u]) {
            ++cnt;
            vector<int> c; // 一维临时点集，初始为空；存当前 SCC 顶点，大小至少 1。
            while (true) {
                int v = stk.top(); // v：当前弹出顶点，1..n；最后一次必为 u。
                stk.pop();
                ins[v] = false;
                bel[v] = cnt;
                c.push_back(v);
                if (v == u)
                    break;
            }
            scc.push_back(c);
        }
    }

    // run()：无参数，返回 void；遍历 DFS 森林，完成全图 SCC。
    // 前提：已 init 并加边，尚未运行；时间 O(n+m)，递归栈最坏 O(n)。
    void run() {
        for (int u = 1; u <= n; u++)
            if (!dfn[u])
                dfs(u);
    }

    // addedge(u,v)：参数为有向边起终点1..n；返回void；前提已init且尚未run。
    // 作用：只封装原PPT邻接表push_back；摊还时间O(1)。
    void addedge(int u, int v) {
        e[u].push_back(v);
    }
};

struct Difference {
    struct edge {
        int u, v, w;
    };
    int n;
    vector<edge> e;
    vector<int> x;
    void init(int n_) {
        n = n_;
        e.clear();
        x.assign(n + 1, 0);
    }
    // 加入x[v]-x[u]<=w，未知数1..n。
    void add_constraint(int u, int v, int w) {
        e.push_back({u, v, w});
    }
    bool solve() {
        fill(x.begin(), x.end(), 0);
        for (int i = 1; i <= n; i++) {
            bool changed = false;
            for (auto [u, v, w] : e)
                if (x[v] > x[u] + w) {
                    x[v] = x[u] + w;
                    changed = true;
                    if (i == n)
                        return false;
                }
            if (!changed)
                return true;
        }
        return true;
    }
    // 特例：所有w<=0；求a[i]>=1且a[v]>=a[u]-w的最小解，x=-a。
    bool minimum_positive() {
        SCC scc;
        scc.init(n);
        for (auto [u, v, w] : e) {
            assert(w <= 0);
            scc.addedge(u, v);
        }
        scc.run();
        int k = scc.cnt;
        vector<vector<pair<int, int>>> g(k + 1);
        vector<int> d(k + 1), ans(k + 1, 1);
        for (auto [u, v, w] : e) {
            u = scc.bel[u];
            v = scc.bel[v];
            if (u == v) {
                if (w < 0)
                    return false;
            } else {
                g[u].push_back({v, -w});
                d[v]++;
            }
        }
        queue<int> q;
        for (int u = 1; u <= k; u++)
            if (!d[u])
                q.push(u);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (auto [v, w] : g[u]) {
                ans[v] = max(ans[v], ans[u] + w);
                if (!--d[v])
                    q.push(v);
            }
        }
        for (int u = 1; u <= n; u++)
            x[u] = -ans[scc.bel[u]];
        return true;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    Difference g;
    g.init(n);
    while (m--) {
        int c, d, y;
        cin >> c >> d >> y;
        g.add_constraint(d, c, y);
    }
    if (!g.solve()) {
        cout << "NO\n";
        return;
    }
    for (int i = 1; i <= n; i++)
        cout << g.x[i] << (i == n ? '\n' : ' ');
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
