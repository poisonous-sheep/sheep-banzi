#include <bits/stdc++.h>
using namespace std;
#define int long long

// DFS序依赖背包：选节点则继续DFS下一点，不选则跳过其整个子树；依赖环先缩点为共同选择的软件包。
// O(nM)时间/空间；SCC另加O(n+m)。
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
struct DependencyKnapsack {
    static constexpr int INF = 4000000000000000000LL;
    int n, M, tot;
    vector<vector<int>> son;
    vector<int> id, r, w, a;
    vector<vector<int>> dp;
    DependencyKnapsack(int n = 0, int M = 0) {
        init(n, M);
    }
    void init(int n_, int m) {
        n = n_;
        M = m;
        tot = 0;
        son.assign(n + 1, {});
        id.assign(n + 2, 0);
        r = w = a = id;
        dp.clear();
    }
    void add_edge(int u, int v) {
        son[u].push_back(v);
    }
    void dfs(int u) {
        id[++tot] = u;
        for (int v : son[u])
            dfs(v);
        r[u] = tot + 1;
    }
    int run(int root, bool exact = false) {
        tot = 0;
        dfs(root);
        dp.assign(tot + 2, vector<int>(M + 1, exact ? -INF : 0));
        dp[tot + 1][0] = 0;
        for (int i = tot; i >= 1; i--) {
            int u = id[i];
            for (int j = 0; j <= M; j++) {
                dp[i][j] = dp[r[u]][j];
                if (j >= w[u] && dp[i + 1][j - w[u]] > -INF)
                    dp[i][j] = max(dp[i][j], dp[i + 1][j - w[u]] + a[u]);
            }
        }
        return dp[1][M];
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    DependencyKnapsack t(n, m);
    for (int i = 1; i <= n; i++) {
        int p;
        cin >> p >> t.a[i];
        t.w[i] = 1;
        t.add_edge(p, i);
    }
    cout << t.run(0, true) << '\n';
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
